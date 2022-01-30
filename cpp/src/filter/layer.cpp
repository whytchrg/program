
#include "layer.h"

Layer::Layer() {

  m_data = nlohmann::json::array();

  m_blend = new Blend();
  m_film = new Film();
  m_data.push_back(m_film->init());
  m_data.push_back(m_blend->init());

}

nlohmann::json Layer::init(std::string type) {
  m_type = type;

  return m_data;
}

nlohmann::json Layer::update(nlohmann::json data, std::string type) {

  m_type = type;

  nlohmann::json new_data = nlohmann::json::array();

  new_data.push_back(m_film->update(data[0]));
  new_data.push_back(m_blend->update(data[1]));

  m_data = new_data;

  return m_data;
}

void Layer::frame(cv::Mat& image, std::size_t frame) {

  std::size_t width, height;

  width  = image.cols;
  height = image.rows;

  cv::Mat film = m_film->frame(frame, width, height);

  // m_blend->process(image, film);
}

void Layer::frame(stk::StkFrames& audio, std::size_t frame) {

  std::size_t length = audio.frames();

  stk::StkFrames film = m_film->frame(length);

  // m_blend->process(audio, film);
}

void Layer::process(std::vector<cv::Mat>& images, stk::StkFrames& audio) {

  if (m_type == "audio") {

    std::size_t length = audio.frames();
    stk::StkFrames audio_film;

    audio_film = m_film->frame(length);
    m_blend->process(audio, audio_film);

  } else {

    std::size_t frames, width, height;
    frames = images.size();
    width = images[0].cols;
    height = images[0].rows;

    std::vector<cv::Mat> image_films;

    image_films = m_film->images(frames, width, height);

    // images = image_films;

    m_blend->process(images, image_films);

  }

}