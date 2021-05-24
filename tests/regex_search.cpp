#include <vector>

#include "regex_search.hpp"

std::vector<RegexTest> test_all_substrings = {
  {"abcde",".*(!x{.+}).*",{"x"},{
    {{0,1}},{{0,2}},{{0,3}},{{0,4}},{{0,5}},{{1,2}},{{1,3}},{{1,4}},{{1,5}},
    {{2,3}},{{2,4}},{{2,5}},{{3,4}},{{3,5}},{{4,5}} }},
  {"!@#()",".*(!x{.+}).*",{"x"},{
    {{0,1}},{{0,2}},{{0,3}},{{0,4}},{{0,5}},{{1,2}},{{1,3}},{{1,4}},{{1,5}},
    {{2,3}},{{2,4}},{{2,5}},{{3,4}},{{3,5}},{{4,5}} }},
  {"A3,.>",".*(!x{.+}).*",{"x"},{
    {{0,1}},{{0,2}},{{0,3}},{{0,4}},{{0,5}},{{1,2}},{{1,3}},{{1,4}},{{1,5}},
    {{2,3}},{{2,4}},{{2,5}},{{3,4}},{{3,5}},{{4,5}} }},
  {"?/';]",".*(!x{.+}).*",{"x"},{
    {{0,1}},{{0,2}},{{0,3}},{{0,4}},{{0,5}},{{1,2}},{{1,3}},{{1,4}},{{1,5}},
    {{2,3}},{{2,4}},{{2,5}},{{3,4}},{{3,5}},{{4,5}} }}
};

std::vector<RegexTest> test_character_sets = {
  {"aa!",".*!x{\\d\\w\\W}.*",{ },{ }},
  {"0!!",".*!x{\\d\\w\\W}.*",{ },{ }},
  {"0aa",".*!x{\\d\\w\\W}.*",{ },{ }},
  {"0a!",".*!x{\\d\\w\\W}.*",{"x"},{ {{0,3}} }},
  {"1A?",".*!x{\\d\\w\\W}.*",{"x"},{ {{0,3}} }},
  {"23*",".*!x{\\d\\w\\W}.*",{"x"},{ {{0,3}} }}
};

std::vector<RegexTest> test_concat = {
  {"aaaaaaaaaa",".*(!x{d+}!y{d+}).*",{ },{ }},
  {"aaaaadaaaa",".*(!x{d+}!y{d+}).*",{ },{ }},
  {"aaaaaaaddd",".*(!x{d+}!y{d+}).*",{"x","y"},{
    {{7,8},{8,9}},{{7,8},{8,10}},{{7,9},{9,10}},{{8,9},{9,10}} }}
};

std::vector<RegexTest> test_concat_adv = {
  {"dddaaaaddd",".*(!x{(a|d)+}!y{b+}).*",{ },{ }},
  {"dddabaaddd",".*(!x{(a|d)+}!y{b+}).*",{"x","y"},{
    {{0,4},{4,5}},{{1,4},{4,5}},{{2,4},{4,5}},{{3,4},{4,5}} }}
};

std::vector<RegexTest> test_concat_order = {
  {"aaaaaaaaaa",".*(!y{d+}!x{d+}).*",{ },{ }},
  {"aaaaadaaaa",".*(!y{d+}!x{d+}).*",{ },{ }},
  {"aaaaaaaddd",".*(!y{d+}!x{d+}).*",{"x","y"},{
    {{8,9},{7,8}},{{8,10},{7,8}},{{9,10},{7,9}},{{9,10},{8,9}} }}
};

std::vector<RegexTest> test_disjunction = {
  {"aaaaaaaaaa",".*(!x{d+}|!x{b+}).*",{ },{ }},
  {"aaaaadaaaa",".*(!x{d+}|!x{b+}).*",{"x"},{ {{5,6}} }},
  {"aaaaaaaddd",".*(!x{d+}|!x{b+}).*",{"x"},{
    {{7,8}},{{7,9}},{{7,10}},{{8,9}},{{8,10}},{{9,10}} }},
  {"dddaaaaaaa",".*(!x{d+}|!x{b+}).*",{"x"},{
    {{0,1}},{{0,2}},{{0,3}},{{1,2}},{{1,3}},{{2,3}} }},
  {"dddaaaaddd",".*(!x{d+}|!x{b+}).*",{"x"},{
    {{0,1}},{{0,2}},{{0,3}},{{1,2}},{{1,3}},{{2,3}},{{7,8}},{{7,9}},{{7,10}},
    {{8,9}},{{8,10}},{{9,10}} }},
  {"dddabaaddd",".*(!x{d+}|!x{b+}).*",{"x"},{
    {{0,1}},{{0,2}},{{0,3}},{{1,2}},{{1,3}},{{2,3}},{{4,5}},{{7,8}},{{7,9}},
    {{7,10}},{{8,9}},{{8,10}},{{9,10}} }}
};

std::vector<RegexTest> test_disjunction_inverse = {
  {"aaaaaaaaaa",".*(!x{b+}|!x{d+}).*",{ },{ }},
  {"aaaaadaaaa",".*(!x{b+}|!x{d+}).*",{"x"},{ {{5,6}} }},
  {"aaaaaaaddd",".*(!x{b+}|!x{d+}).*",{"x"},{
    {{7,8}},{{7,9}},{{7,10}},{{8,9}},{{8,10}},{{9,10}} }},
  {"dddaaaaaaa",".*(!x{b+}|!x{d+}).*",{"x"},{
    {{0,1}},{{0,2}},{{0,3}},{{1,2}},{{1,3}},{{2,3}} }},
  {"dddaaaaddd",".*(!x{b+}|!x{d+}).*",{"x"},{
    {{0,1}},{{0,2}},{{0,3}},{{1,2}},{{1,3}},{{2,3}},{{7,8}},{{7,9}},{{7,10}},
    {{8,9}},{{8,10}},{{9,10}} }},
  {"dddabaaddd",".*(!x{b+}|!x{d+}).*",{"x"},{
    {{0,1}},{{0,2}},{{0,3}},{{1,2}},{{1,3}},{{2,3}},{{4,5}},{{7,8}},{{7,9}},
    {{7,10}},{{8,9}},{{8,10}},{{9,10}} }}
};

std::vector<RegexTest> test_disjunction_of_equal_re = {
  {"aaaaaaaaaa",".*(!x{d*|d*}).*",{"x"},{
    {{0,0}},{{1,1}},{{2,2}},{{3,3}},{{4,4}},{{5,5}},{{6,6}},{{7,7}},{{8,8}},
    {{9,9}},{{10,10}} }},
  {"aaaaadaaaa",".*(!x{d*|d*}).*",{"x"},{
    {{0,0}},{{1,1}},{{2,2}},{{3,3}},{{4,4}},{{5,5}},{{5,6}},{{6,6}},{{7,7}},
    {{8,8}},{{9,9}},{{10,10}} }},
  {"aaaaaaaddd",".*(!x{d*|d*}).*",{"x"},{
    {{0,0}},{{1,1}},{{2,2}},{{3,3}},{{4,4}},{{5,5}},{{6,6}},{{7,7}},{{7,8}},
    {{7,9}},{{7,10}},{{8,8}},{{8,9}},{{8,10}},{{9,9}},{{9,10}},{{10,10}} }},
  {"dddaaaaaaa",".*(!x{d*|d*}).*",{"x"},{
    {{0,0}},{{0,1}},{{0,2}},{{0,3}},{{1,1}},{{1,2}},{{1,3}},{{2,2}},{{2,3}},
    {{3,3}},{{4,4}},{{5,5}},{{6,6}},{{7,7}},{{8,8}},{{9,9}},{{10,10}} }},
  {"dddaaaaddd",".*(!x{d*|d*}).*",{"x"},{
    {{0,0}},{{0,1}},{{0,2}},{{0,3}},{{1,1}},{{1,2}},{{1,3}},{{2,2}},{{2,3}},
    {{3,3}},{{4,4}},{{5,5}},{{6,6}},{{7,7}},{{7,8}},{{7,9}},{{7,10}},{{8,8}},
    {{8,9}},{{8,10}},{{9,9}},{{9,10}},{{10,10}} }},
  {"dddabaaddd",".*(!x{d*|d*}).*",{"x"},{
    {{0,0}},{{0,1}},{{0,2}},{{0,3}},{{1,1}},{{1,2}},{{1,3}},{{2,2}},{{2,3}},
    {{3,3}},{{4,4}},{{5,5}},{{6,6}},{{7,7}},{{7,8}},{{7,9}},{{7,10}},{{8,8}},
    {{8,9}},{{8,10}},{{9,9}},{{9,10}},{{10,10}} }}
};

std::vector<RegexTest> test_disjunction_of_equal_vars = {
  {"aaaaaaaaaa",".*(!x{d*}|!x{d*}).*",{"x"},{
    {{0,0}},{{1,1}},{{2,2}},{{3,3}},{{4,4}},{{5,5}},{{6,6}},{{7,7}},{{8,8}},
    {{9,9}},{{10,10}} }},
  {"aaaaadaaaa",".*(!x{d*}|!x{d*}).*",{"x"},{
    {{0,0}},{{1,1}},{{2,2}},{{3,3}},{{4,4}},{{5,5}},{{5,6}},{{6,6}},{{7,7}},
    {{8,8}},{{9,9}},{{10,10}} }},
  {"aaaaaaaddd",".*(!x{d*}|!x{d*}).*",{"x"},{
    {{0,0}},{{1,1}},{{2,2}},{{3,3}},{{4,4}},{{5,5}},{{6,6}},{{7,7}},{{7,8}},
    {{7,9}},{{7,10}},{{8,8}},{{8,9}},{{8,10}},{{9,9}},{{9,10}},{{10,10}} }},
  {"dddaaaaaaa",".*(!x{d*}|!x{d*}).*",{"x"},{
    {{0,0}},{{0,1}},{{0,2}},{{0,3}},{{1,1}},{{1,2}},{{1,3}},{{2,2}},{{2,3}},
    {{3,3}},{{4,4}},{{5,5}},{{6,6}},{{7,7}},{{8,8}},{{9,9}},{{10,10}} }},
  {"dddaaaaddd",".*(!x{d*}|!x{d*}).*",{"x"},{
    {{0,0}},{{0,1}},{{0,2}},{{0,3}},{{1,1}},{{1,2}},{{1,3}},{{2,2}},{{2,3}},
    {{3,3}},{{4,4}},{{5,5}},{{6,6}},{{7,7}},{{7,8}},{{7,9}},{{7,10}},{{8,8}},
    {{8,9}},{{8,10}},{{9,9}},{{9,10}},{{10,10}} }},
  {"dddabaaddd",".*(!x{d*}|!x{d*}).*",{"x"},{
    {{0,0}},{{0,1}},{{0,2}},{{0,3}},{{1,1}},{{1,2}},{{1,3}},{{2,2}},{{2,3}},
    {{3,3}},{{4,4}},{{5,5}},{{6,6}},{{7,7}},{{7,8}},{{7,9}},{{7,10}},{{8,8}},
    {{8,9}},{{8,10}},{{9,9}},{{9,10}},{{10,10}} }}
};

std::vector<RegexTest> test_disjunctive_overlaps = {
  {"aaaaaaaaaa",".*(!x{d*}|!x{dd}).*",{"x"},{
    {{0,0}},{{1,1}},{{2,2}},{{3,3}},{{4,4}},{{5,5}},{{6,6}},{{7,7}},{{8,8}},
    {{9,9}},{{10,10}} }},
  {"aaaaadaaaa",".*(!x{d*}|!x{dd}).*",{"x"},{
    {{0,0}},{{1,1}},{{2,2}},{{3,3}},{{4,4}},{{5,5}},{{5,6}},{{6,6}},{{7,7}},
    {{8,8}},{{9,9}},{{10,10}} }},
  {"aaaaaaaddd",".*(!x{d*}|!x{dd}).*",{"x"},{
    {{0,0}},{{1,1}},{{2,2}},{{3,3}},{{4,4}},{{5,5}},{{6,6}},{{7,7}},{{7,8}},
    {{7,9}},{{7,10}},{{8,8}},{{8,9}},{{8,10}},{{9,9}},{{9,10}},{{10,10}} }},
  {"dddaaaaaaa",".*(!x{d*}|!x{dd}).*",{"x"},{
    {{0,0}},{{0,1}},{{0,2}},{{0,3}},{{1,1}},{{1,2}},{{1,3}},{{2,2}},{{2,3}},
    {{3,3}},{{4,4}},{{5,5}},{{6,6}},{{7,7}},{{8,8}},{{9,9}},{{10,10}} }},
  {"dddaaaaddd",".*(!x{d*}|!x{dd}).*",{"x"},{
    {{0,0}},{{0,1}},{{0,2}},{{0,3}},{{1,1}},{{1,2}},{{1,3}},{{2,2}},{{2,3}},
    {{3,3}},{{4,4}},{{5,5}},{{6,6}},{{7,7}},{{7,8}},{{7,9}},{{7,10}},{{8,8}},
    {{8,9}},{{8,10}},{{9,9}},{{9,10}},{{10,10}} }},
  {"dddabaaddd",".*(!x{d*}|!x{dd}).*",{"x"},{
    {{0,0}},{{0,1}},{{0,2}},{{0,3}},{{1,1}},{{1,2}},{{1,3}},{{2,2}},{{2,3}},
    {{3,3}},{{4,4}},{{5,5}},{{6,6}},{{7,7}},{{7,8}},{{7,9}},{{7,10}},{{8,8}},
    {{8,9}},{{8,10}},{{9,9}},{{9,10}},{{10,10}} }}
};

std::vector<RegexTest> test_first_and_last_element = {
  {"a","!x{.}.*!y{.}",{ },{ }},
  {"aa","!x{.}.*!y{.}",{"x","y"},{ {{0,1},{1,2}} }},
  {"aaa","!x{.}.*!y{.}",{"x","y"},{ {{0,1},{2,3}} }},
  {"aaaaaaaaaa","!x{.}.*!y{.}",{"x","y"},{ {{0,1},{9,10}} }}
};

std::vector<RegexTest> test_first_element = {
  {"a","!x{.}.*",{"x"},{ {{0,1}} }},
  {"aaaaaaaaaa","!x{.}.*",{"x"},{ {{0,1}} }}
};

std::vector<RegexTest> test_kleene_star = {
  {"aaaaa",".*!x{.*}.*",{"x"},{
    {{0,0}},{{0,1}},{{0,2}},{{0,3}},{{0,4}},{{0,5}},{{1,1}},{{1,2}},{{1,3}},
    {{1,4}},{{1,5}},{{2,2}},{{2,3}},{{2,4}},{{2,5}},{{3,3}},{{3,4}},{{3,5}},
    {{4,4}},{{4,5}},{{5,5}} }}
};

std::vector<RegexTest> test_last_element = {
  {"a",".*!x{.}",{"x"},{ {{0,1}} }},
  {"aaaaaaaaaa",".*!x{.}",{"x"},{ {{9,10}} }}
};

std::vector<RegexTest> test_multiple_operators = {
  {"|aadsdsfa|",".*!x{\\|(a[^a]|[^a])*a?\\|}.*",{ },{ }},
  {"|dasdawdaa|",".*!x{\\|(a[^a]|[^a])*a?\\|}.*",{ },{ }},
  {"|sdaadsdaadd|",".*!x{\\|(a[^a]|[^a])*a?\\|}.*",{ },{ }},
  {"|sdfdd|",".*!x{\\|(a[^a]|[^a])*a?\\|}.*",{"x"},{ {{0,7}} }},
  {"|fsdasadd|",".*!x{\\|(a[^a]|[^a])*a?\\|}.*",{"x"},{ {{0,10}} }},
  {"|asdsa|",".*!x{\\|(a[^a]|[^a])*a?\\|}.*",{"x"},{ {{0,7}} }}
};

std::vector<RegexTest> test_multiple_paths = {
  {"aaaaa",".*(!x{!y{(a|b)*}}|!x{!y{(a|d)*}}).*",{"x","y"},{
    {{0,0},{0,0}},{{0,1},{0,1}},{{0,2},{0,2}},{{0,3},{0,3}},{{0,4},{0,4}},
    {{0,5},{0,5}},{{1,1},{1,1}},{{1,2},{1,2}},{{1,3},{1,3}},{{1,4},{1,4}},
    {{1,5},{1,5}},{{2,2},{2,2}},{{2,3},{2,3}},{{2,4},{2,4}},{{2,5},{2,5}},
    {{3,3},{3,3}},{{3,4},{3,4}},{{3,5},{3,5}},{{4,4},{4,4}},{{4,5},{4,5}},
    {{5,5},{5,5}} }},
  {"aadaa",".*(!x{!y{(a|b)*}}|!x{!y{(a|d)*}}).*",{"x","y"},{
    {{0,0},{0,0}},{{0,1},{0,1}},{{0,2},{0,2}},{{0,3},{0,3}},{{0,4},{0,4}},
    {{0,5},{0,5}},{{1,1},{1,1}},{{1,2},{1,2}},{{1,3},{1,3}},{{1,4},{1,4}},
    {{1,5},{1,5}},{{2,2},{2,2}},{{2,3},{2,3}},{{2,4},{2,4}},{{2,5},{2,5}},
    {{3,3},{3,3}},{{3,4},{3,4}},{{3,5},{3,5}},{{4,4},{4,4}},{{4,5},{4,5}},
    {{5,5},{5,5}} }},
  {"aaadd",".*(!x{!y{(a|b)*}}|!x{!y{(a|d)*}}).*",{"x","y"},{
    {{0,0},{0,0}},{{0,1},{0,1}},{{0,2},{0,2}},{{0,3},{0,3}},{{0,4},{0,4}},
    {{0,5},{0,5}},{{1,1},{1,1}},{{1,2},{1,2}},{{1,3},{1,3}},{{1,4},{1,4}},
    {{1,5},{1,5}},{{2,2},{2,2}},{{2,3},{2,3}},{{2,4},{2,4}},{{2,5},{2,5}},
    {{3,3},{3,3}},{{3,4},{3,4}},{{3,5},{3,5}},{{4,4},{4,4}},{{4,5},{4,5}},
    {{5,5},{5,5}} }},
  {"dddaa",".*(!x{!y{(a|b)*}}|!x{!y{(a|d)*}}).*",{"x","y"},{
    {{0,0},{0,0}},{{0,1},{0,1}},{{0,2},{0,2}},{{0,3},{0,3}},{{0,4},{0,4}},
    {{0,5},{0,5}},{{1,1},{1,1}},{{1,2},{1,2}},{{1,3},{1,3}},{{1,4},{1,4}},
    {{1,5},{1,5}},{{2,2},{2,2}},{{2,3},{2,3}},{{2,4},{2,4}},{{2,5},{2,5}},
    {{3,3},{3,3}},{{3,4},{3,4}},{{3,5},{3,5}},{{4,4},{4,4}},{{4,5},{4,5}},
    {{5,5},{5,5}} }},
  {"ddaad",".*(!x{!y{(a|b)*}}|!x{!y{(a|d)*}}).*",{"x","y"},{
    {{0,0},{0,0}},{{0,1},{0,1}},{{0,2},{0,2}},{{0,3},{0,3}},{{0,4},{0,4}},
    {{0,5},{0,5}},{{1,1},{1,1}},{{1,2},{1,2}},{{1,3},{1,3}},{{1,4},{1,4}},
    {{1,5},{1,5}},{{2,2},{2,2}},{{2,3},{2,3}},{{2,4},{2,4}},{{2,5},{2,5}},
    {{3,3},{3,3}},{{3,4},{3,4}},{{3,5},{3,5}},{{4,4},{4,4}},{{4,5},{4,5}},
    {{5,5},{5,5}} }},
  {"dabdd",".*(!x{!y{(a|b)*}}|!x{!y{(a|d)*}}).*",{"x","y"},{
    {{0,0},{0,0}},{{0,1},{0,1}},{{0,2},{0,2}},{{1,1},{1,1}},{{1,2},{1,2}},
    {{1,3},{1,3}},{{2,2},{2,2}},{{2,3},{2,3}},{{3,3},{3,3}},{{3,4},{3,4}},
    {{3,5},{3,5}},{{4,4},{4,4}},{{4,5},{4,5}},{{5,5},{5,5}} }}
};

std::vector<RegexTest> test_nested_disjunction = {
  {"aaaaaaaaaa",".*(!x{!y{d+}|!y{b+}}).*",{ },{ }},
  {"aaaaadaaaa",".*(!x{!y{d+}|!y{b+}}).*",{"x","y"},{ {{5,6},{5,6}} }},
  {"aaaaaaaddd",".*(!x{!y{d+}|!y{b+}}).*",{"x","y"},{
    {{7,8},{7,8}},{{7,9},{7,9}},{{7,10},{7,10}},{{8,9},{8,9}},{{8,10},{8,10}},
    {{9,10},{9,10}} }},
  {"aaaabaaddd",".*(!x{!y{d+}|!y{b+}}).*",{"x","y"},{
    {{4,5},{4,5}},{{7,8},{7,8}},{{7,9},{7,9}},{{7,10},{7,10}},{{8,9},{8,9}},
    {{8,10},{8,10}},{{9,10},{9,10}} }}
};

std::vector<RegexTest> test_nested_disjunction_inverse = {
  {"aaaaaaaaaa",".*(!x{!y{b+}|!y{d+}}).*",{ },{ }},
  {"aaaaadaaaa",".*(!x{!y{b+}|!y{d+}}).*",{"x","y"},{ {{5,6},{5,6}} }},
  {"aaaaaaaddd",".*(!x{!y{b+}|!y{d+}}).*",{"x","y"},{
    {{7,8},{7,8}},{{7,9},{7,9}},{{7,10},{7,10}},{{8,9},{8,9}},{{8,10},{8,10}},
    {{9,10},{9,10}} }},
  {"aaaabaaddd",".*(!x{!y{b+}|!y{d+}}).*",{"x","y"},{
    {{4,5},{4,5}},{{7,8},{7,8}},{{7,9},{7,9}},{{7,10},{7,10}},{{8,9},{8,9}},
    {{8,10},{8,10}},{{9,10},{9,10}} }}
};

std::vector<RegexTest> test_nested_vars_concat = {
  {"a",".*(!x{!y{a+}}!z{!w{a+}}).*",{ },{ }},
  {"aa",".*(!x{!y{a+}}!z{!w{a+}}).*",{"x","y","z","w"},{
    {{0,1},{0,1},{1,2},{1,2}} }},
  {"aaa",".*(!x{!y{a+}}!z{!w{a+}}).*",{"x","y","z","w"},{
    {{0,1},{0,1},{1,2},{1,2}},{{0,1},{0,1},{1,3},{1,3}},
    {{0,2},{0,2},{2,3},{2,3}},{{1,2},{1,2},{2,3},{2,3}} }}
};

std::vector<RegexTest> test_nested_vars_concat_adv = {
  {"a",".*(!x{!y{(a|b)+}}!z{!w{(a|d)+}}).*",{ },{ }},
  {"bd",".*(!x{!y{(a|b)+}}!z{!w{(a|d)+}}).*",{"x","y","z","w"},{
    {{0,1},{0,1},{1,2},{1,2}} }},
  {"aa",".*(!x{!y{(a|b)+}}!z{!w{(a|d)+}}).*",{"x","y","z","w"},{
    {{0,1},{0,1},{1,2},{1,2}} }},
  {"ad",".*(!x{!y{(a|b)+}}!z{!w{(a|d)+}}).*",{"x","y","z","w"},{
    {{0,1},{0,1},{1,2},{1,2}} }},
  {"aaa",".*(!x{!y{(a|b)+}}!z{!w{(a|d)+}}).*",{"x","y","z","w"},{
    {{0,1},{0,1},{1,2},{1,2}},{{0,1},{0,1},{1,3},{1,3}},
    {{0,2},{0,2},{2,3},{2,3}},{{1,2},{1,2},{2,3},{2,3}} }},
  {"bad",".*(!x{!y{(a|b)+}}!z{!w{(a|d)+}}).*",{"x","y","z","w"},{
    {{0,1},{0,1},{1,2},{1,2}},{{0,1},{0,1},{1,3},{1,3}},
    {{0,2},{0,2},{2,3},{2,3}},{{1,2},{1,2},{2,3},{2,3}} }},
  {"bbdd",".*(!x{!y{(a|b)+}}!z{!w{(a|d)+}}).*",{"x","y","z","w"},{
    {{0,2},{0,2},{2,3},{2,3}},{{0,2},{0,2},{2,4},{2,4}},
    {{1,2},{1,2},{2,3},{2,3}},{{1,2},{1,2},{2,4},{2,4}} }}
};

std::vector<RegexTest> test_nesting_variables = {
  {"aaaaaaaaaa",".*!x{!y{d+}}.*",{ },{ }},
  {"aaaaadaaaa",".*!x{!y{d+}}.*",{"x","y"},{ {{5,6},{5,6}} }},
  {"aaaaaaaddd",".*!x{!y{d+}}.*",{"x","y"},{
    {{7,8},{7,8}},{{7,9},{7,9}},{{7,10},{7,10}},{{8,9},{8,9}},{{8,10},{8,10}},
    {{9,10},{9,10}} }}
};

std::vector<RegexTest> test_nesting_variables_inverse = {
  {"aaaaaaaaaa",".*!y{!x{d+}}.*",{ },{ }},
  {"aaaaadaaaa",".*!y{!x{d+}}.*",{"x","y"},{ {{5,6},{5,6}} }},
  {"aaaaaaaddd",".*!y{!x{d+}}.*",{"x","y"},{
    {{7,8},{7,8}},{{7,9},{7,9}},{{7,10},{7,10}},{{8,9},{8,9}},{{8,10},{8,10}},
    {{9,10},{9,10}} }}
};

std::vector<RegexTest> test_one_or_more_char_match = {
  {"aaaaaaaaaa",".*!x{d+}.*",{ },{ }},
  {"aaaaadaaaa",".*!x{d+}.*",{"x"},{ {{5,6}} }},
  {"aaaaaaaddd",".*!x{d+}.*",{"x"},{
    {{7,8}},{{7,9}},{{7,10}},{{8,9}},{{8,10}},{{9,10}} }},
  {"dddaaaaaaa",".*!x{d+}.*",{"x"},{
    {{0,1}},{{0,2}},{{0,3}},{{1,2}},{{1,3}},{{2,3}} }},
  {"dddaaaaddd",".*!x{d+}.*",{"x"},{
    {{0,1}},{{0,2}},{{0,3}},{{1,2}},{{1,3}},{{2,3}},{{7,8}},{{7,9}},{{7,10}},
    {{8,9}},{{8,10}},{{9,10}} }}
};

std::vector<RegexTest> test_single_char_match = {
  {"aaaaaaaaaa",".*!x{d}.*",{ },{ }},
  {"aaaaadaaaa",".*!x{d}.*",{"x"},{ {{5,6}} }},
  {"aaaaaaaddd",".*!x{d}.*",{"x"},{ {{7,8}},{{8,9}},{{9,10}} }},
  {"dddaaaaaaa",".*!x{d}.*",{"x"},{ {{0,1}},{{1,2}},{{2,3}} }},
  {"dddaaaaddd",".*!x{d}.*",{"x"},{
    {{0,1}},{{1,2}},{{2,3}},{{7,8}},{{8,9}},{{9,10}} }}
};

std::vector<RegexTest> test_specific_element = {
  {"aaaaaaaaaa","....!x{.}.*",{"x"},{ {{4,5}} }},
  {"aaaa","....!x{.}.*",{ },{ }},
  {"aaaaa","....!x{.}.*",{"x"},{ {{4,5}} }}
};

std::vector<RegexTest> test_the_whole_document = {
  {"aaaaaaaaaa","!x{.*}",{"x"},{ {{0,10}} }},
  {"a","!x{.*}",{"x"},{ {{0,1}} }}
};

std::vector<RegexTest> test_two_char_match = {
  {"aaaaaaaaaa",".*!x{dd}.*",{ },{ }},
  {"aaaaadaaaa",".*!x{dd}.*",{ },{ }},
  {"aaaaaaaddd",".*!x{dd}.*",{"x"},{ {{7,9}},{{8,10}} }},
  {"dddaaaaaaa",".*!x{dd}.*",{"x"},{ {{0,2}},{{1,3}} }},
  {"dddaaaaddd",".*!x{dd}.*",{"x"},{ {{0,2}},{{1,3}},{{7,9}},{{8,10}} }}
};