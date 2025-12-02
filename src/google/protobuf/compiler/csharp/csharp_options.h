// Protocol Buffers - Google's data interchange format
// Copyright 2008 Google Inc.  All rights reserved.
//
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file or at
// https://developers.google.com/open-source/licenses/bsd

#ifndef GOOGLE_PROTOBUF_COMPILER_CSHARP_CSHARP_OPTIONS_H__
#define GOOGLE_PROTOBUF_COMPILER_CSHARP_CSHARP_OPTIONS_H__

#include <string>

namespace google {
namespace protobuf {
namespace compiler {
namespace csharp {

// Generator options (used by csharp_generator.cc):
struct Options {
  Options()
      : file_extension(".cs"),
        base_namespace(""),
        base_namespace_specified(false),
        internal_access(false),
        serializable(false),
        strip_nonfunctional_codegen(false),
        preserve_names(false),
        preserve_enum_names(false),
        generate_specified(false) {}
  // Extension of the generated file. Defaults to ".cs"
  std::string file_extension;
  // Base namespace to use to create directory hierarchy. Defaults to "".
  // This option allows the simple creation of a conventional C# file layout,
  // where directories are created relative to a project-specific base
  // namespace. For example, in a project with a base namespace of PetShop, a
  // proto of user.proto with a C# namespace of PetShop.Model.Shared would
  // generate Model/Shared/User.cs underneath the specified --csharp_out
  // directory.
  //
  // If no base namespace is specified, all files are generated in the
  // --csharp_out directory, with no subdirectories created automatically.
  std::string base_namespace;
  // Whether the base namespace has been explicitly specified by the user.
  // This is required as the base namespace can be explicitly set to the empty
  // string, meaning "create a full directory hierarchy, starting from the first
  // segment of the namespace."
  bool base_namespace_specified;
  // Whether the generated classes should have accessibility level of "internal".
  // Defaults to false that generates "public" classes.
  bool internal_access;
  // Whether the generated classes should have a global::System.Serializable attribute added
  // Defaults to false
  bool serializable;
  // If true, strip out nonfunctional codegen.
  bool strip_nonfunctional_codegen;
  // If true, preserve original field and enum value names without converting
  // to PascalCase. For example, "user_name" stays as "user_name" instead of
  // becoming "UserName", and "BRT_XX" stays as "BRT_XX" instead of "BrtXx".
  bool preserve_names;
  // If true, preserve original enum value names without converting to PascalCase.
  // For example, "BRT_XX" stays as "BRT_XX" instead of "BrtXx".
  // This only affects enum values, not field names.
  bool preserve_enum_names;
  // If true, generate xxxSpecified property for optional fields in addition
  // to HasXxx property. This is useful for compatibility with some serialization
  // frameworks like .NET XML serialization.
  bool generate_specified;
};

}  // namespace csharp
}  // namespace compiler
}  // namespace protobuf
}  // namespace google

#endif  // GOOGLE_PROTOBUF_COMPILER_CSHARP_CSHARP_OPTIONS_H__
