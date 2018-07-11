#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

inline std::string wrap(std::string s) { std::string result; auto new_line = true; auto skip_line = false; auto escape = false; auto comment = false; for (const auto c : s) { if (new_line && c == '#') { skip_line = true; new_line = false; } if (c == '\n') { skip_line = false; new_line = true; } if (skip_line || c == '\r' || c == '\n' || new_line && c == ' ') continue; const auto was_new_line = new_line; new_line = false; if (c == '"') escape = !escape; if (!escape && c == '/') { if (comment) { skip_line = true; comment = false; } else comment = true; continue; } if (comment && c != '/') result += '/'; comment = false; if (was_new_line && !result.empty()) result += " "; result += c; } return result; } inline void shrink(const std::vector<std::string>& file_paths) { std::ostringstream result; for (unsigned i = 0; i < file_paths.size(); ++i) { if (i > 0) result << " "; std::ifstream ifs(file_paths.at(i)); result << wrap({ std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>() }); } std::ofstream ofs("shrink_.h"); ofs << result.str() << std::endl; }
