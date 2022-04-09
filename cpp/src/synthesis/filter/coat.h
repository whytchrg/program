
#ifndef coat_h
#define coat_h

#include <thread>
#include <future>

#include "../../functionality/data.h"
#include "../../functionality/math.h"

class Coat {

private:

  nlohmann::json m_coat = nlohmann::json::array();

  std::string m_type{"spectrum"};

protected:

  Coat() {
    std::vector<std::string> type_options{"spectrum"};
    m_coat.push_back(data::init_str("type", type_options, m_type));
  };

  nlohmann::json coat_data() {
    return m_coat;
  };

public:

  virtual nlohmann::json data() = 0;

  virtual nlohmann::json update(nlohmann::json data) = 0;

  virtual cv::Mat image_frame(cv::Mat& image, std::size_t frame_index) = 0;

  virtual cv::Mat audio_frame(cv::Mat& audio, std::size_t frame_index) = 0;

};

#endif // coat_h END