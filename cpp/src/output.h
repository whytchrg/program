
#ifndef output_h
#define output_h

#include "out/hsl.h"

class Output {

  private:

    std::string m_type;

    nlohmann::json m_data;

    Out* m_base;

  public:
    Output();

    nlohmann::json init();

    nlohmann::json update(nlohmann::json data, std::string type);

    void process(std::vector<cv::Mat>& images, stk::StkFrames& audio);

};

#endif /* output_h */
