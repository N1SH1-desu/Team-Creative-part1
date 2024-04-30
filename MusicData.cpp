#include "MusicData.h"

using namespace std;

NoteManager::NoteManager()
{
    m_note_2d.resize(2);
    m_notes_size.resize(2);

    fill(m_notes_size.begin(), m_notes_size.end(), 0);
}

NoteManager::~NoteManager()
{
}

void NoteManager::AddNote(int col, int row, int num, int length, MusicDataOption* p)
{
    Note note{};
    note.pos = 0.0f;
    note.perfect_pos = 60.0 * 4 * (row + (double)num / length) / p->bpm - p->offset;
    note.Flag = false;
    
    m_note_2d[col].push_back(note);
    m_notes_size[col]++;
}

double NoteManager::getNoteTiming(int col , int num)
{
    if (col > 2) return -1.0;
    if (num > m_notes_size[col] - 1) return -1.0;

    return m_note_2d[col][num].perfect_pos;
}


MusicData::MusicData(const std::string& filename) :
    m_file(),
    m_file_name(),
    m_file_options(),
    m_file_data(),
    m_noteManager(nullptr),
    m_options()
{
    m_noteManager = new NoteManager;
    m_file_name = filename;
    GetFileData();
}

bool MusicData::GetFileData()
{
    m_file.open(m_file_name, std::ios::in);
    if (!m_file)
    {
        return false;
    }
    string music_option_data;
    getline(m_file, music_option_data, ',');
    m_file_options << music_option_data;

    Load_MusicOptions();
    m_file.seekg(2, ios::cur);

    string music_notes;
    getline(m_file, music_notes, '.');
    m_file_data << music_notes;
    Load_NotesData();

    return true;
}

bool MusicData::GetFileData(const string& filename)
{
    m_file_name = filename;
    m_file.open(m_file_name, std::ios::in);
    string music_option_data;
    getline(m_file, music_option_data, ',');
    m_file_options << music_option_data;

    Load_MusicOptions();
    m_file.seekg(2, ios::cur);

    string music_notes;
    getline(m_file, music_notes, '.');
    m_file_data << music_notes;
    Load_NotesData();

    return true;
}

void MusicData::Load_MusicOptions()
{
    string row_str;
    while ( getline(m_file_options, row_str) )
    {
        if (row_str == "#START")
        {
            m_options.isStart = true;
            break;
        }

        stringstream data(row_str);
        string name;
        getline(data, name, ':');
        if (name == "TITLE")
            data >> m_options.song_name;
        else if (name == "BPM")
            data >> m_options.bpm;
        else if (name == "OFFSET")
            data >> m_options.offset;
        else if (name == "WAVE")
            data >> m_options.song_path;
    }
}

void MusicData::Load_NotesData()
{
    string data;
    for (int row = 0; getline(m_file_data, data); row++)
    {
        stringstream data_stream(data);
        string separate_data;
        for (int col = 0; getline(data_stream, separate_data, ','); col++)
        {
            int length = (int)separate_data.size();
            for (int i = 0; i < length; i++)
            {
                if ('1' <= separate_data[i] && separate_data[i] <= '9')
                {
                    // AddNote(int col, int row, int num, int length, MusicDataOption option)
                    m_noteManager->AddNote(col, row, i, length, &m_options);
                }
            }
        }
    }
}
