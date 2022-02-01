
#ifndef program_h
#define program_h

#include <string>

#include "settings.h"
#include "filter.h"
#include "output.h"

typedef struct {
  std::size_t frame;
  cv::Mat image;
  cv::Mat audio;
} frame;

class Program {

  private:

    nlohmann::json m_data;

    // just for the data
    Settings m_settings;
    Filter m_filter;
    Output m_output;

    std::vector<frame> m_frames;

    frame create_frame(std::size_t frame_index);

    frame get_frame(std::size_t f);

  public:
    Program();

    // •   work()

    // <-  data()
    // <-> update(data) / including play ???

    // <-  read(frame)  / returns image and audio data

    std::string work();

    nlohmann::json data();
    nlohmann::json update(nlohmann::json data);

    frame read(std::size_t f);



    nlohmann::json init();

    void preview(std::vector<cv::Mat>& images, stk::StkFrames& audio);

    void save();

};

#endif /* program_h */
