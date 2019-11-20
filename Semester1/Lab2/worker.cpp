//
// Created by Gomer on 31.10.2019.
//
#include "grep.h"
#include "readfile.h"
#include "writefile.h"
#include "replace.h"
#include "sort.h"
#include "dump.h"
#include "worker.h"

void worker::process(const char *workFile) {
  parser p;
  p.parse(workFile);
  auto sequence = p.getSequence();
  auto parsedText = p.getParsedText();
  size_t counter = 1;
  for (const auto &id : sequence) {
    Iblock *block = blockFactory::Instance().create(parsedText[id].first);
    if (counter == 1) {
      if (block->getType() != blockType::IN) {
        throw std::logic_error("Wrong sequence of functions");
      }
    }
    else if (counter == sequence.size()) {
      if (block->getType() != blockType::OUT) {
        throw std::logic_error("Wrong sequence of functions");
      }
    }
    else{
      if (block->getType() != blockType::INOUT){
        throw std::logic_error("Wrong sequence of functions");
      }
    }
    block->execute((parsedText[id].second), text);
    counter++;
    delete block;
  }
}


