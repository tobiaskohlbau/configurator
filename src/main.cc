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

#include <iostream>

#include <gflags/gflags.h>

#include <config.hpp>

static bool ValidateFilename(const char *flagname, const std::string &value) {
  return value[0] != '\0';
}
DEFINE_string(filename, "", "Configuration file");
DEFINE_validator(filename, &ValidateFilename);

int main(int argc, char *argv[]) {
  gflags::SetUsageMessage("use config");
  gflags::SetVersionString("1.0.0");
  gflags::ParseCommandLineFlags(&argc, &argv, true);

  try {
    auto cfg = std::make_shared<Config>(FLAGS_filename);

    auto harris = cfg->detector<detector::Harris>();
    auto random = cfg->detector<detector::Random>();

    std::cout << "name: " << harris->name()
              << " samplingRate: " << harris->samplingRate() << std::endl;
    std::cout << "name: " << random->name()
              << " samplingDistribution: " << random->samplingDistribution()
              << std::endl;
  } catch (const std::invalid_argument &e) {
    std::cout << e.what() << std::endl;
    return 2;
  }

  return 0;
}
