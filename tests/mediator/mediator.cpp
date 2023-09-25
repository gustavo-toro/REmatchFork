#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#undef private
#include "evaluation/algorithm_class.hpp"
#include "evaluation/extended_va/dfa/extended_det_va.hpp"
#include "mediator/mediator.hpp"
#include "../evaluation/mapping_helpers.hpp"

namespace rematch::testing {

void run_mediator_test(std::string regex, std::string document,
                       std::vector<mediator::Mapping> expected_mappings);
extern char EOF_char;

TEST_CASE("the mediator throws an exception when the variable is not in the regex") {
  Parser parser = Parser("!x{a}");
  std::string document = "a";
  document += EOF_char;

  LogicalVA logical_va = parser.get_logical_va();
  ExtendedVA extended_va = ExtendedVA(logical_va);
  extended_va.clean_for_determinization();
  auto extended_det_va = ExtendedDetVA(extended_va);
  std::shared_ptr<VariableCatalog> variable_catalog = parser.get_variable_catalog();
  SearchDFA search_dfa = SearchDFA(logical_va);

  Mediator mediator = Mediator(search_dfa, extended_det_va, variable_catalog, document);

  mediator::Mapping* mapping = mediator.next();
  REQUIRE_THROWS(mapping->get_span_of_variable("y"));
}

TEST_CASE("the mediator returns null pointer when there are no mappings") {
  Parser parser = Parser("!x{a}");
  std::string document = "b";
  document += EOF_char;

  LogicalVA logical_va = parser.get_logical_va();
  ExtendedVA extended_va = ExtendedVA(logical_va);
  extended_va.clean_for_determinization();
  auto extended_det_va = ExtendedDetVA(extended_va);
  std::shared_ptr<VariableCatalog> variable_catalog = parser.get_variable_catalog();
  SearchDFA search_dfa = SearchDFA(logical_va);

  Mediator mediator = Mediator(search_dfa, extended_det_va, variable_catalog, document);

  mediator::Mapping* mapping = mediator.next();
  REQUIRE(mapping == nullptr);
}

TEST_CASE("the mediator returns an empty mapping if there are no captures") {
  Parser parser = Parser("a");
  std::string document = "a";
  document += EOF_char;

  LogicalVA logical_va = parser.get_logical_va();
  ExtendedVA extended_va = ExtendedVA(logical_va);
  extended_va.clean_for_determinization();
  auto extended_det_va = ExtendedDetVA(extended_va);
  std::shared_ptr<VariableCatalog> variable_catalog = parser.get_variable_catalog();
  SearchDFA search_dfa = SearchDFA(logical_va);

  Mediator mediator = Mediator(search_dfa, extended_det_va, variable_catalog, document);

  mediator::Mapping* mapping = mediator.next();
  REQUIRE(mapping->get_spans_map().size() == 0);
}

TEST_CASE("the mediator returns the correct mappings for !x{a} over aaa") {
  std::string document = "aaa";
  std::string regex = "!x{a}";
  std::vector<mediator::Mapping> expected_mappings = {
    mediator::Mapping({{"x", {0, 1}}}),
    mediator::Mapping({{"x", {1, 2}}}),
    mediator::Mapping({{"x", {2, 3}}})
  };

  run_mediator_test(regex, document, expected_mappings);
}

TEST_CASE("the mediator returns the correct mappings when using quantifier +") {
  std::string document = "aa aa";
  std::string regex = "!x{a+}";
  std::vector<mediator::Mapping> expected_mappings = {
    mediator::Mapping({{"x", {0, 1}}}),
    mediator::Mapping({{"x", {1, 2}}}),
    mediator::Mapping({{"x", {0, 2}}}),
    mediator::Mapping({{"x", {3, 4}}}),
    mediator::Mapping({{"x", {4, 5}}}),
    mediator::Mapping({{"x", {3, 5}}})
  };

  run_mediator_test(regex, document, expected_mappings);
}

TEST_CASE("the mediator returns the correct mappings when using quantifier ?") {
  std::string document = "aabaaabba";
  std::string regex = "!x{a[ab]?b}";
  std::vector<mediator::Mapping> expected_mappings = {
    mediator::Mapping({{"x", {1, 3}}}),
    mediator::Mapping({{"x", {0, 3}}}),
    mediator::Mapping({{"x", {5, 7}}}),
    mediator::Mapping({{"x", {4, 7}}}),
    mediator::Mapping({{"x", {5, 8}}})
  };

  run_mediator_test(regex, document, expected_mappings);
}

TEST_CASE("the mediator returns the correct mappings when using quantifier *") {
  std::string document = "thathathat";
  std::string regex = "!x{t(hat)*}";
  std::vector<mediator::Mapping> expected_mappings = {
    mediator::Mapping({{"x", {0, 1}}}), mediator::Mapping({{"x", {3, 4}}}),
    mediator::Mapping({{"x", {0, 4}}}), mediator::Mapping({{"x", {6, 7}}}),
    mediator::Mapping({{"x", {3, 7}}}), mediator::Mapping({{"x", {0, 7}}}),
    mediator::Mapping({{"x", {9, 10}}}), mediator::Mapping({{"x", {6, 10}}}),
    mediator::Mapping({{"x", {3, 10}}}), mediator::Mapping({{"x", {0, 10}}})
  };

  run_mediator_test(regex, document, expected_mappings);
}

TEST_CASE("the mediator returns the correct mappings when using nested variables") {
  std::string document = "ab ab";
  std::string regex = "!x{!y{a}.+}";
  std::vector<mediator::Mapping> expected_mappings = {
    mediator::Mapping({{"x", {0, 2}}, {"y", {0, 1}}}),
    mediator::Mapping({{"x", {0, 3}}, {"y", {0, 1}}}),
    mediator::Mapping({{"x", {0, 4}}, {"y", {0, 1}}}),
    mediator::Mapping({{"x", {3, 5}}, {"y", {3, 4}}}),
    mediator::Mapping({{"x", {0, 5}}, {"y", {0, 1}}})
  };

  run_mediator_test(regex, document, expected_mappings);
}

TEST_CASE("the mediator returns the correct mappings when using alternation") {
  std::string document = "Meat, vegetables and spices (or sauces).";
  std::string regex = "!condiment{sauce|spice|syrup}";
  std::vector<mediator::Mapping> expected_mappings = {
    mediator::Mapping({{"condiment", {21, 26}}}),
    mediator::Mapping({{"condiment", {32, 37}}})
  };

  run_mediator_test(regex, document, expected_mappings);
}

TEST_CASE("the mediator returns the correct mappings when using char classes") {
  std::string document = "man pages are your friend";
  std::string regex = "!man{[a-z]{4}}";
  std::vector<mediator::Mapping> expected_mappings = {
    mediator::Mapping({{"man", {4, 8}}}),
    mediator::Mapping({{"man", {5, 9}}}),
    mediator::Mapping({{"man", {14, 18}}}),
    mediator::Mapping({{"man", {14, 18}}}),
    mediator::Mapping({{"man", {19, 23}}}),
    mediator::Mapping({{"man", {20, 24}}}),
    mediator::Mapping({{"man", {21, 25}}})
  };

  run_mediator_test(regex, document, expected_mappings);
}

void run_mediator_test(std::string regex, std::string document,
                       std::vector<mediator::Mapping> expected_mappings) {
  Parser parser = Parser(regex);
  document += EOF_char;

  LogicalVA logical_va = parser.get_logical_va();
  ExtendedVA extended_va = ExtendedVA(logical_va);
  extended_va.clean_for_determinization();
  auto extended_det_va = ExtendedDetVA(extended_va);
  std::shared_ptr<VariableCatalog> variable_catalog = parser.get_variable_catalog();
  SearchDFA search_dfa = SearchDFA(logical_va);

  Mediator mediator = Mediator(search_dfa, extended_det_va, variable_catalog, document);

  std::ostringstream info_os;
  info_os << "Actual mappings:" << std::endl;

  mediator::Mapping* actual_mapping = mediator.next();
  while (actual_mapping != nullptr) {
    info_os << *actual_mapping;
    INFO(info_os.str());
    REQUIRE(contains_mapping(expected_mappings, *actual_mapping));
    remove_mapping_from_expected(expected_mappings, *actual_mapping);
    actual_mapping = mediator.next();
  }

  INFO(info_os.str());
  REQUIRE(expected_mappings.size() == 0);
}

}  // namespace rematch::testing
