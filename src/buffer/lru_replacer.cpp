//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// lru_replacer.cpp
//
// Identification: src/buffer/lru_replacer.cpp
//
// Copyright (c) 2015-2019, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include "buffer/lru_replacer.h"

namespace bustub {

LRUReplacer::LRUReplacer(size_t num_pages) {}

LRUReplacer::~LRUReplacer() = default;

bool LRUReplacer::Victim(frame_id_t *frame_id) {
  if (replace_list_.empty()) {
    return false;
  }
  *frame_id = replace_list_.front();
  replace_list_.pop_front();
  frame_pos_.erase(*frame_id);
  
  return true;
}

void LRUReplacer::Pin(frame_id_t frame_id) {
  auto iter = frame_pos_.find(frame_id);
  if (iter != frame_pos_.end()) {
    auto replace_list_iter = iter->second;
    replace_list_.erase(replace_list_iter);
    frame_pos_.erase(frame_id);
  }
}

void LRUReplacer::Unpin(frame_id_t frame_id) {
  if (frame_pos_.find(frame_id) == frame_pos_.end()) {
    replace_list_.push_back(frame_id);
    auto iter = --replace_list_.end();
    frame_pos_.insert({frame_id, iter});
  }
}

size_t LRUReplacer::Size() { return replace_list_.size(); }

}  // namespace bustub
