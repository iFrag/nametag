// This file is part of NameTag.
//
// Copyright 2013 by Institute of Formal and Applied Linguistics, Faculty of
// Mathematics and Physics, Charles University in Prague, Czech Republic.
//
// NameTag is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation, either version 3 of
// the License, or (at your option) any later version.
//
// NameTag is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with NameTag.  If not, see <http://www.gnu.org/licenses/>.

#include <memory>

#include "ner/bilou_ner_trainer.h"
#include "ner/ner_ids.h"
#include "tagger/tagger.h"
#include "utils/file_ptr.h"

using namespace ufal::nametag;

int main(int argc, char* argv[]) {
  if (argc < 2) runtime_errorf("Usage: %s ner_identifier [options]", argv[0]);

  ner_id id;
  if (!ner_ids::parse(argv[1], id)) runtime_errorf("Cannot parse ner_identifier '%s'!\n", argv[1]);

  switch (id) {
    case ner_ids::BILOU_NER:
      {
        if (argc < 9) runtime_errorf("Usage: %s %s tagger_id[:tagger_options] features iterations missing_weight initial_alpha final_alpha gaussian [heldout_data]  ", argv[0], argv[1]);

        // Encode the ner_id
        fputc(id, stdout);

        // Create and encode the tagger
        unique_ptr<tagger> tagger(tagger::create_and_encode_instance(argv[2], stdout));
        if (!tagger) runtime_errorf("Cannot load and encode tagger!");

        // Parse options
        network_parameters parameters;
        const char* features_file = argv[3];
        parameters.iterations = atoi(argv[4]);
        parameters.missing_weight = atof(argv[5]);
        parameters.initial_learning_rate = atof(argv[6]);
        parameters.final_learning_rate = atof(argv[7]);
        parameters.gaussian_sigma = atof(argv[8]);
        const char* heldout_file = argc == 9 ? nullptr : argv[9];

        // Open needed files
        file_ptr features = fopen(features_file, "r");
        if (!features) runtime_errorf("Cannot open features file '%s'!", features_file);

        file_ptr heldout;
        if (heldout_file) {
          heldout = fopen(heldout_file, "r");
          if (!heldout) runtime_errorf("Cannot open heldout file '%s'!", heldout_file);
        }

        // Encode the ner itself
        bilou_ner_trainer::train(parameters, *tagger, features, stdin, heldout, stdout);

        eprintf("Recognizer saved.\n");
        break;
      }
    default:
      runtime_errorf("Unimplemented ner_identifier '%s'!\n", argv[1]);
  }

  return 0;
}