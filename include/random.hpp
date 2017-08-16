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

#ifndef DETECTOR_RANDOM_H_
#define DETECTOR_RANDOM_H_

#include <string>

#include <detector.h>

#include <json/json.hpp>

namespace detector {
class Random : public Detector {
 public:
  Random() : sampling_distribution_(0){};
  Random(const nlohmann::json &j) {
    sampling_distribution_ = j.at("samplingDistribution").get<int>();
  }
  ~Random() = default;

  std::string name() const override { return "random"; }
  int samplingDistribution() { return sampling_distribution_; }
  void setSamplingDistribution(int dist) { sampling_distribution_ = dist; }

 private:
  int sampling_distribution_;
};

void from_json(const nlohmann::json &j, Random &p) {
  p.setSamplingDistribution(j.at("samplingDistribution").get<int>());
}
} /* detector */

#endif /* DETECTOR_RANDOM_H_ */
