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

// This file declares the document outline viewer.

#ifndef OUTLINE_VIEWER_HPP
#define OUTLINE_VIEWER_HPP

#include "document.hpp"
#include <set>
#include <string>
#include <vector>

// Outline viewer class. This class stores the expansion and focus states
// between invocations.
class OutlineViewer {
 public:
  // Constructs an instance of OutlineViewer that displays the given Outline.
  // Does not take ownership of the outline object.
  OutlineViewer(const Document::OutlineItem *outline);
  // Displays the outline view and enter the event loop. If the user selected a
  // page to jump to, returns true and sets page to the destination page number.
  // Otherwise returns false.
  bool Show(int *dest_page);

 private:
  // Handle to the outline we display. Does not have ownership.
  const Document::OutlineItem *_outline;
  // All expanded outline items.
  std::set<const Document::OutlineItem *> _expanded_items;
  // The outline flattened out into an array of lines.
  std::vector<std::string> _lines;
  // Index in _lines of the currently highlighted item.
  int _selected_item;
  // Index in _lines of the first displayed item.
  int _first_item;

  // Flatten out _outline to _lines, according to _expanded_items.
  void Flatten();
  // Recursively flatten the outline item using preorder traversal.
  void FlattenRecursive(const Document::OutlineItem *item, int depth);
};

#endif
