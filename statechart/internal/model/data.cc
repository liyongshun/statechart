// Copyright 2018 The StateChart Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "statechart/internal/model/data.h"

#include <glog/logging.h>

#include "absl/strings/str_cat.h"
#include "absl/strings/substitute.h"
#include "statechart/internal/datamodel.h"
#include "statechart/internal/runtime.h"
#include "statechart/internal/utility.h"

namespace state_chart {
namespace model {

Data::Data(const string& location, const string& expr)
    : location_(location), expr_(expr) {}

// override
bool Data::Execute(Runtime* runtime) const {
  VLOG(1) << absl::Substitute("Data($0, $1)", location_, expr_);
  if (!runtime->mutable_datamodel()->Declare(location_)) {
    runtime->EnqueueExecutionError(
        absl::StrCat("'Data' declaration failure at location: ", location_));
    return false;
  }
  if (!expr_.empty() &&
      !runtime->mutable_datamodel()->AssignExpression(location_, expr_)) {
    runtime->EnqueueExecutionError(
        absl::StrCat("'Data' assign failure: ", location_, " = ",
                     expr_.empty() ? "[empty]" : expr_));
    return false;
  }
  return true;
}

}  // namespace model
}  // namespace state_chart
