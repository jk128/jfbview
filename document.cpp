/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *  Copyright (C) 2012 Chuan Ji <jichuan89@gmail.com>                        *
 *                                                                           *
 *  Licensed under the Apache License, Version 2.0 (the "License");          *
 *  you may not use this file except in compliance with the License.         *
 *  You may obtain a copy of the License at                                  *
 *                                                                           *
 *   http://www.apache.org/licenses/LICENSE-2.0                              *
 *                                                                           *
 *  Unless required by applicable law or agreed to in writing, software      *
 *  distributed under the License is distributed on an "AS IS" BASIS,        *
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. *
 *  See the License for the specific language governing permissions and      *
 *  limitations under the License.                                           *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

// Implementation for methods declared in document.hpp.

#include "document.hpp"
#include <string>
#include <vector>

Document::~Document() { }

Document::OutlineItem::~OutlineItem() {
}

const std::string& Document::OutlineItem::GetTitle() const {
  return _title;
}

int Document::OutlineItem::GetNumChildren() const {
  return _children.size();
}

const Document::OutlineItem* Document::OutlineItem::GetChild(int i) const {
  return _children[i].get();
}

std::vector<Document::SearchResult> Document::Search(
    const std::string& search_string,
    int start_page,
    int max_num_search_results) {
  std::vector<SearchResult> results;
  for (int page = start_page; results.size() < max_num_search_results; ++page) {
    const std::vector<SearchResult>& results_on_page = SearchOnPage(
        search_string, page);
    results.insert(
        results.end(),
        results_on_page.begin(),
        results_on_page.end());
  }
  return results;
}
