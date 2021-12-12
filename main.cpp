/*
 * main.cpp
 * Copyright (C) 2021 Stephan Seitz <stephan.seitz@fau.de>
 *
 * Distributed under terms of the GPLv3 license.
 */

#include "schema_generated.h"
#include <cstdlib>
#include <fmt/core.h>
#include <fstream>
#include <iostream>
#include <vector>

auto main(int argc, char **argv) -> int {
  std::vector<uint8_t> storage(1024);

  using namespace MyGame::Sample;
  flatbuffers::FlatBufferBuilder fbb;

  // auto pos = Vec3(2, 3, 5);
  // auto mon1 = CreateMonster(fbb, &pos);
  // MonsterT monster{.pos = std::make_unique<Vec3>(1, 2, 4)};
  // auto mon2 = CreateMonster(fbb, &monster);
  // std::vector vec = {mon1, mon2};
  // fbb.Finish(CreateMonsterVecDirect(fbb, &vec));

  MonsterVecT monsters;
  monsters.monsters.emplace_back(std::make_unique<MonsterT>(MonsterT{.pos = std::make_unique<Vec3>(1, 2, 4)}));
  monsters.monsters.emplace_back(std::make_unique<MonsterT>(MonsterT{.pos = std::make_unique<Vec3>(3, 6, 8)}));
  fbb.Finish(MonsterVec::Pack(fbb, &monsters));

  {
    std::ofstream outStream("foo", std::ios::binary | std::ios::out);
    outStream.write((char *)fbb.GetBufferPointer(), fbb.GetSize());
  }
  {
    std::ifstream istream("foo", std::ios::binary | std::ios::in);
    std::vector<char> bytes((std::istreambuf_iterator<char>(istream)),
                            std::istreambuf_iterator<char>());
    MonsterVecT vec;
    GetMonsterVec(bytes.data())->UnPackTo(&vec);
    for (auto &mon : vec.monsters) {
      fmt::print("({},{},{})\n", mon->pos->x(), mon->pos->y(), mon->pos->z());
    }
  }

  return EXIT_SUCCESS;
}
