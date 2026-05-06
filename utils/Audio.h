#pragma once
#include <SFML/Audio.hpp>
#include <vector>
#include <string>

struct Audio
{
    sf::Music music;
    std::vector<std::string> tracks;
    int currentIndex = 0;

    Audio()
    {
        tracks = {
            "Assets/The Crystal Method - Over it (Asphalt 8) (LYRİCS).wav",
            "Assets/professional_griefers.wav",
            "Assets/animals.wav"
        };
        music.setLoop(true);
        music.setVolume(50.f);
        openCurrent();
    }

    void play()  { music.play();  }
    void stop()  { music.stop();  }
    void pause() { music.pause(); }

    // Advance to the next track and play it from the start
    void nextTrack()
    {
        currentIndex = (currentIndex + 1) % (int)tracks.size();
        music.stop();
        openCurrent();
        music.play();
    }

private:
    void openCurrent()
    {
        music.openFromFile(tracks[currentIndex]);
        music.setLoop(true);
        music.setVolume(50.f);
    }
};
