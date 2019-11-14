//
// Created by Gomer on 31.10.2019.
//
#include "worker.h"
void worker::process(const char *workFile) {
  parser p;
  p.parse(workFile);
  auto sequence = p.getSequence();
  auto parsedText = p.getParsedText();
  if ((parsedText[sequence[0]].first != "readfile") || (parsedText[sequence[sequence.size() - 1]].first != "writefile")){
    throw std::logic_error("First function must be 'readfile' and last function must be 'writefile'");
  }
  IblockFactory::Instance().add<Grep>("grep");
  IblockFactory::Instance().add<Readfile>("readfile");
  IblockFactory::Instance().add<Writefile>("writefile");
  IblockFactory::Instance().add<Sort>("sort");
  IblockFactory::Instance().add<Dump>("dump");
  IblockFactory::Instance().add<Replace>("replace");
  for (const auto &id : sequence) {
    Iblock *block = IblockFactory::Instance().create(parsedText[id].first);
    block->execute((parsedText[id].second), text);
    delete block;
  }
}
