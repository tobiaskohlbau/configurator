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

#ifndef CONFIG_H_
#define CONFIG_H_

#include <fstream>
#include <map>
#include <stdexcept>
#include <string>

#include <harris.hpp>
#include <random.hpp>

#include <json/json.hpp>

class Config {
 public:
  Config() = default;
  Config(const std::string filename) { this->loadFromFile(filename); }
  ~Config() = default;

  void loadFromFile(const std::string &fn) {
    std::ifstream f(fn);
    if (!f.is_open()) throw std::invalid_argument("failed to open config file");
    nlohmann::json j;
    try {
      f >> j;
    } catch (const nlohmann::detail::parse_error &e) {
      throw std::invalid_argument("failed to parse json file (illformed?)");
    }

    auto jsonGenerators = j["generators"];
    if (jsonGenerators.empty())
      throw std::invalid_argument("failed to find generators object");

    auto h = std::make_shared<detector::Harris>(jsonGenerators.at("harris"));
    auto r = std::make_shared<detector::Random>(jsonGenerators.at("random"));
    detectors_[h->name()] = h;
    detectors_[r->name()] = r;
  };

  template <typename T>
  std::shared_ptr<T> detector() {
    for (auto const &d : detectors_) {
      auto ptr = std::dynamic_pointer_cast<T>(d.second);
      if (ptr) {
        return ptr;
      }
    }
    return nullptr;
  };

  std::shared_ptr<detector::Detector> detectorByName(const std::string &name) {
    return detectors_[name];
  }

 private:
  std::map<std::string, std::shared_ptr<detector::Detector>> detectors_;
};

#endif /* CONFIG_H_ */
