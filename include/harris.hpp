//    Copyright 2017 Tobias Kohlbau
//
//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
//
//        http://www.apache.org/licenses/LICENSE-2.0
//
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.

#ifndef DETECTOR_HARRIS_H_
#define DETECTOR_HARRIS_H_

#include <string>

#include <detector.h>

#include <json/json.hpp>

namespace detector {

class Harris : public Detector {
 public:
  Harris() : sampling_rate_(0){};
  Harris(const nlohmann::json &j) {
    sampling_rate_ = j.at("samplingRate").get<int>();
  }
  ~Harris() = default;

  std::string name() const override { return "harris"; }
  int samplingRate() { return sampling_rate_; }
  void setSamplingRate(int rate) { sampling_rate_ = rate; }

 private:
  int sampling_rate_;
};

void from_json(const nlohmann::json &j, Harris &p) {
  p.setSamplingRate(j.at("samplingRate").get<int>());
}
} /* detector */

#endif /* DETECTOR_HARRIS_H_ */
