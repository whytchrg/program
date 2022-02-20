
#ifndef program_h
#define program_h

#include <string>
#include <chrono>
#include <thread>
#include <mutex>

#include "settings.h"
#include "filter.h"
#include "output.h"

typedef struct {
  std::size_t index;
  cv::Mat image;
  cv::Mat audio;
} frame;

class Program {

  private:

    bool m_work = true;

    bool m_update = false;

    nlohmann::json m_data;

    std::size_t m_frame_time, m_buffer_size{2}, m_current_frame{0};

    Settings m_settings;
    Filter   m_filter;
    Output   m_output;
    std::mutex m_objects_mutex;

    std::vector<frame> m_buffer;
    std::mutex m_buffer_mutex;

    void create_frame(std::size_t frame_index);

    void clear_buffer();

    void update_buffer();


    std::size_t last_buffer_index();

    frame get_frame(std::size_t frame_index);

    bool frame_exists(std::size_t frame_index);

    std::thread m_main;
    void main();

  public:
    Program();

    // •   main()

    // <-  data()
    // <-> update(data) / including play ???

    // <-  read(frame)  / returns image and audio data

    // void main();

    nlohmann::json data();

    nlohmann::json update(nlohmann::json data);

    void read(cv::Mat& image, cv::Mat& audio, std::size_t frame_index);

    void quit();


    // void preview(std::vector<cv::Mat>& images, stk::StkFrames& audio);

    // void save();

};

#endif /* program_h */
