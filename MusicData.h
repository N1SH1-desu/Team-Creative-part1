#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

struct Note
{
    float pos = 0.0f;
    double perfect_pos = 0.0;
    bool Flag = false;
};

struct MusicDataOption
{
    std::string song_name;
    std::string song_path;
    int bpm;
    float offset;
    bool isStart;

    MusicDataOption() :
        song_name(),
        song_path(),
        bpm(0),
        offset(0),
        isStart(false)
    {}
};

class NoteManager
{
public:
    NoteManager();
    ~NoteManager();

    void AddNote(int, int, int, int, MusicDataOption*);

    double getNoteTiming(int, int);

private:
    std::vector<std::vector<Note>> m_note_2d;
    std::vector<unsigned int> m_notes_size;
};


class MusicData
{
public:
    MusicData() = delete;
    MusicData(const MusicData&) = delete;
    MusicData& operator=(const MusicData&) = delete;


    MusicData(const std::string&);
    

    bool GetFileData();
    bool GetFileData(const std::string&);
    void Load_MusicOptions();
    void Load_NotesData();

    const std::stringstream& getOptionStream() const { return m_file_options; }
    const std::stringstream& getDataStream() const { return m_file_data; }

    const MusicDataOption& getOptions() const { return m_options; }
    NoteManager& getNoteManager() const { return *m_noteManager; }

private:
    std::string m_file_name;
    std::ifstream m_file;

    std::stringstream m_file_options;
    std::stringstream m_file_data;

    NoteManager* m_noteManager;
    MusicDataOption m_options;
};
