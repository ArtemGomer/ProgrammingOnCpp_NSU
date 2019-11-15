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
  Iblock *blockCheck = blockFactory::Instance().create(parsedText[sequence.front()].first);
  if (blockCheck->getType() != blockType::IN){
    delete(blockCheck);
    throw std::logic_error("First function must be 'readfile' and last function must be 'writefile'");
  }
  blockCheck = blockFactory::Instance().create(parsedText[sequence.back()].first);
  if (blockCheck->getType() != blockType::OUT){
    delete(blockCheck);
    throw std::logic_error("First function must be 'readfile' and last function must be 'writefile'");
  }
  for (const auto &id : sequence) {
    Iblock *block = blockFactory::Instance().create(parsedText[id].first);
    block->execute((parsedText[id].second), text);
    delete block;
  }
}


