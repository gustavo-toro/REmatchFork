
// Generated from REmatchParser.g4 by ANTLR 4.10.1


#include "REmatchParserVisitor.h"

#include "REmatchParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct REmatchParserStaticData final {
  REmatchParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  REmatchParserStaticData(const REmatchParserStaticData&) = delete;
  REmatchParserStaticData(REmatchParserStaticData&&) = delete;
  REmatchParserStaticData& operator=(const REmatchParserStaticData&) = delete;
  REmatchParserStaticData& operator=(REmatchParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

std::once_flag rematchparserParserOnceFlag;
REmatchParserStaticData *rematchparserParserStaticData = nullptr;

void rematchparserParserInitialize() {
  assert(rematchparserParserStaticData == nullptr);
  auto staticData = std::make_unique<REmatchParserStaticData>(
    std::vector<std::string>{
      "root", "alternation", "expr", "element", "group", "parentheses", 
      "assignation", "atom", "characterClass", "ccAtom", "ccRange", "ccLiteral", 
      "ccEscapes", "ccOther", "literal", "escapes", "other", "sharedAtom", 
      "quantifier", "quantity", "quantExact", "quantRange", "quantMin", 
      "quantMax", "number"
    },
    std::vector<std::string>{
      "", "'\\d'", "'\\D'", "'\\h'", "'\\H'", "'\\n'", "'\\N'", "'\\s'", 
      "'\\S'", "'\\v'", "'\\V'", "'\\w'", "'\\W'", "", "'|'", "'!'", "'{'", 
      "'}'", "'('", "')'", "','", "'\\u003F'", "'+'", "'*'", "'^'", "'-'", 
      "'['", "']'", "'\\'", "", "", "'.'"
    },
    std::vector<std::string>{
      "", "DECIMAL_DIGIT", "NOT_DECIMAL_DIGIT", "HORIZONTAL_WHITESPACE", 
      "NOT_HORIZONTAL_WHITESPACE", "NEW_LINE", "NOT_NEW_LINE", "WHITESPACE", 
      "NOT_WHITESPACE", "VERTICAL_WHITESPACE", "NOT_VERTICAL_WHITESPACE", 
      "WORD_CHAR", "NOT_WORD_CHAR", "VARNAME", "PIPE", "EXCLAMAITON", "L_CURLY", 
      "R_CURLY", "L_PAR", "R_PAR", "COMMA", "QUESTION", "PLUS", "STAR", 
      "HAT", "HYPHEN", "L_BRACK", "R_BRACK", "BACKSLASH", "ALPHA", "DIGIT", 
      "DOT", "UNRECOGNIZED"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,32,163,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,1,0,1,0,1,0,1,1,1,1,1,1,5,1,57,8,1,10,
  	1,12,1,60,9,1,1,2,4,2,63,8,2,11,2,12,2,64,1,3,1,3,3,3,69,8,3,1,4,1,4,
  	1,4,3,4,74,8,4,1,5,1,5,1,5,1,5,1,6,1,6,1,6,1,6,1,6,1,6,1,7,1,7,1,7,3,
  	7,89,8,7,1,8,1,8,3,8,93,8,8,1,8,4,8,96,8,8,11,8,12,8,97,1,8,1,8,1,9,1,
  	9,1,9,3,9,105,8,9,1,10,1,10,1,10,1,10,1,11,1,11,3,11,113,8,11,1,12,1,
  	12,1,12,1,13,1,13,1,14,1,14,3,14,122,8,14,1,15,1,15,1,15,1,16,1,16,1,
  	17,1,17,1,18,1,18,1,18,1,18,1,18,1,18,1,18,3,18,138,8,18,1,19,1,19,1,
  	19,1,19,3,19,144,8,19,1,20,1,20,1,21,1,21,1,21,1,21,1,22,1,22,1,22,1,
  	23,1,23,1,23,1,24,4,24,159,8,24,11,24,12,24,160,1,24,0,0,25,0,2,4,6,8,
  	10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,0,3,2,0,24,
  	25,27,28,5,0,14,14,16,19,21,23,26,28,31,31,1,0,1,12,157,0,50,1,0,0,0,
  	2,53,1,0,0,0,4,62,1,0,0,0,6,66,1,0,0,0,8,73,1,0,0,0,10,75,1,0,0,0,12,
  	79,1,0,0,0,14,88,1,0,0,0,16,90,1,0,0,0,18,104,1,0,0,0,20,106,1,0,0,0,
  	22,112,1,0,0,0,24,114,1,0,0,0,26,117,1,0,0,0,28,121,1,0,0,0,30,123,1,
  	0,0,0,32,126,1,0,0,0,34,128,1,0,0,0,36,137,1,0,0,0,38,143,1,0,0,0,40,
  	145,1,0,0,0,42,147,1,0,0,0,44,151,1,0,0,0,46,154,1,0,0,0,48,158,1,0,0,
  	0,50,51,3,2,1,0,51,52,5,0,0,1,52,1,1,0,0,0,53,58,3,4,2,0,54,55,5,14,0,
  	0,55,57,3,4,2,0,56,54,1,0,0,0,57,60,1,0,0,0,58,56,1,0,0,0,58,59,1,0,0,
  	0,59,3,1,0,0,0,60,58,1,0,0,0,61,63,3,6,3,0,62,61,1,0,0,0,63,64,1,0,0,
  	0,64,62,1,0,0,0,64,65,1,0,0,0,65,5,1,0,0,0,66,68,3,8,4,0,67,69,3,36,18,
  	0,68,67,1,0,0,0,68,69,1,0,0,0,69,7,1,0,0,0,70,74,3,10,5,0,71,74,3,12,
  	6,0,72,74,3,14,7,0,73,70,1,0,0,0,73,71,1,0,0,0,73,72,1,0,0,0,74,9,1,0,
  	0,0,75,76,5,18,0,0,76,77,3,2,1,0,77,78,5,19,0,0,78,11,1,0,0,0,79,80,5,
  	15,0,0,80,81,5,13,0,0,81,82,5,16,0,0,82,83,3,2,1,0,83,84,5,17,0,0,84,
  	13,1,0,0,0,85,89,3,16,8,0,86,89,3,34,17,0,87,89,3,28,14,0,88,85,1,0,0,
  	0,88,86,1,0,0,0,88,87,1,0,0,0,89,15,1,0,0,0,90,92,5,26,0,0,91,93,5,24,
  	0,0,92,91,1,0,0,0,92,93,1,0,0,0,93,95,1,0,0,0,94,96,3,18,9,0,95,94,1,
  	0,0,0,96,97,1,0,0,0,97,95,1,0,0,0,97,98,1,0,0,0,98,99,1,0,0,0,99,100,
  	5,27,0,0,100,17,1,0,0,0,101,105,3,20,10,0,102,105,3,34,17,0,103,105,3,
  	28,14,0,104,101,1,0,0,0,104,102,1,0,0,0,104,103,1,0,0,0,105,19,1,0,0,
  	0,106,107,3,22,11,0,107,108,5,25,0,0,108,109,3,22,11,0,109,21,1,0,0,0,
  	110,113,3,24,12,0,111,113,3,26,13,0,112,110,1,0,0,0,112,111,1,0,0,0,113,
  	23,1,0,0,0,114,115,5,28,0,0,115,116,7,0,0,0,116,25,1,0,0,0,117,118,8,
  	0,0,0,118,27,1,0,0,0,119,122,3,30,15,0,120,122,3,32,16,0,121,119,1,0,
  	0,0,121,120,1,0,0,0,122,29,1,0,0,0,123,124,5,28,0,0,124,125,7,1,0,0,125,
  	31,1,0,0,0,126,127,8,1,0,0,127,33,1,0,0,0,128,129,7,2,0,0,129,35,1,0,
  	0,0,130,138,5,21,0,0,131,138,5,22,0,0,132,138,5,23,0,0,133,134,5,16,0,
  	0,134,135,3,38,19,0,135,136,5,17,0,0,136,138,1,0,0,0,137,130,1,0,0,0,
  	137,131,1,0,0,0,137,132,1,0,0,0,137,133,1,0,0,0,138,37,1,0,0,0,139,144,
  	3,40,20,0,140,144,3,42,21,0,141,144,3,44,22,0,142,144,3,46,23,0,143,139,
  	1,0,0,0,143,140,1,0,0,0,143,141,1,0,0,0,143,142,1,0,0,0,144,39,1,0,0,
  	0,145,146,3,48,24,0,146,41,1,0,0,0,147,148,3,48,24,0,148,149,5,20,0,0,
  	149,150,3,48,24,0,150,43,1,0,0,0,151,152,3,48,24,0,152,153,5,20,0,0,153,
  	45,1,0,0,0,154,155,5,20,0,0,155,156,3,48,24,0,156,47,1,0,0,0,157,159,
  	5,30,0,0,158,157,1,0,0,0,159,160,1,0,0,0,160,158,1,0,0,0,160,161,1,0,
  	0,0,161,49,1,0,0,0,13,58,64,68,73,88,92,97,104,112,121,137,143,160
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  rematchparserParserStaticData = staticData.release();
}

}

REmatchParser::REmatchParser(TokenStream *input) : REmatchParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

REmatchParser::REmatchParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  REmatchParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *rematchparserParserStaticData->atn, rematchparserParserStaticData->decisionToDFA, rematchparserParserStaticData->sharedContextCache, options);
}

REmatchParser::~REmatchParser() {
  delete _interpreter;
}

const atn::ATN& REmatchParser::getATN() const {
  return *rematchparserParserStaticData->atn;
}

std::string REmatchParser::getGrammarFileName() const {
  return "REmatchParser.g4";
}

const std::vector<std::string>& REmatchParser::getRuleNames() const {
  return rematchparserParserStaticData->ruleNames;
}

const dfa::Vocabulary& REmatchParser::getVocabulary() const {
  return rematchparserParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView REmatchParser::getSerializedATN() const {
  return rematchparserParserStaticData->serializedATN;
}


//----------------- RootContext ------------------------------------------------------------------

REmatchParser::RootContext::RootContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

REmatchParser::AlternationContext* REmatchParser::RootContext::alternation() {
  return getRuleContext<REmatchParser::AlternationContext>(0);
}

tree::TerminalNode* REmatchParser::RootContext::EOF() {
  return getToken(REmatchParser::EOF, 0);
}


size_t REmatchParser::RootContext::getRuleIndex() const {
  return REmatchParser::RuleRoot;
}


std::any REmatchParser::RootContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<REmatchParserVisitor*>(visitor))
    return parserVisitor->visitRoot(this);
  else
    return visitor->visitChildren(this);
}

REmatchParser::RootContext* REmatchParser::root() {
  RootContext *_localctx = _tracker.createInstance<RootContext>(_ctx, getState());
  enterRule(_localctx, 0, REmatchParser::RuleRoot);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(50);
    alternation();
    setState(51);
    match(REmatchParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AlternationContext ------------------------------------------------------------------

REmatchParser::AlternationContext::AlternationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<REmatchParser::ExprContext *> REmatchParser::AlternationContext::expr() {
  return getRuleContexts<REmatchParser::ExprContext>();
}

REmatchParser::ExprContext* REmatchParser::AlternationContext::expr(size_t i) {
  return getRuleContext<REmatchParser::ExprContext>(i);
}

std::vector<tree::TerminalNode *> REmatchParser::AlternationContext::PIPE() {
  return getTokens(REmatchParser::PIPE);
}

tree::TerminalNode* REmatchParser::AlternationContext::PIPE(size_t i) {
  return getToken(REmatchParser::PIPE, i);
}


size_t REmatchParser::AlternationContext::getRuleIndex() const {
  return REmatchParser::RuleAlternation;
}


std::any REmatchParser::AlternationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<REmatchParserVisitor*>(visitor))
    return parserVisitor->visitAlternation(this);
  else
    return visitor->visitChildren(this);
}

REmatchParser::AlternationContext* REmatchParser::alternation() {
  AlternationContext *_localctx = _tracker.createInstance<AlternationContext>(_ctx, getState());
  enterRule(_localctx, 2, REmatchParser::RuleAlternation);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(53);
    expr();
    setState(58);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == REmatchParser::PIPE) {
      setState(54);
      match(REmatchParser::PIPE);
      setState(55);
      expr();
      setState(60);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprContext ------------------------------------------------------------------

REmatchParser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<REmatchParser::ElementContext *> REmatchParser::ExprContext::element() {
  return getRuleContexts<REmatchParser::ElementContext>();
}

REmatchParser::ElementContext* REmatchParser::ExprContext::element(size_t i) {
  return getRuleContext<REmatchParser::ElementContext>(i);
}


size_t REmatchParser::ExprContext::getRuleIndex() const {
  return REmatchParser::RuleExpr;
}


std::any REmatchParser::ExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<REmatchParserVisitor*>(visitor))
    return parserVisitor->visitExpr(this);
  else
    return visitor->visitChildren(this);
}

REmatchParser::ExprContext* REmatchParser::expr() {
  ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, getState());
  enterRule(_localctx, 4, REmatchParser::RuleExpr);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(62); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(61);
      element();
      setState(64); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << REmatchParser::DECIMAL_DIGIT)
      | (1ULL << REmatchParser::NOT_DECIMAL_DIGIT)
      | (1ULL << REmatchParser::HORIZONTAL_WHITESPACE)
      | (1ULL << REmatchParser::NOT_HORIZONTAL_WHITESPACE)
      | (1ULL << REmatchParser::NEW_LINE)
      | (1ULL << REmatchParser::NOT_NEW_LINE)
      | (1ULL << REmatchParser::WHITESPACE)
      | (1ULL << REmatchParser::NOT_WHITESPACE)
      | (1ULL << REmatchParser::VERTICAL_WHITESPACE)
      | (1ULL << REmatchParser::NOT_VERTICAL_WHITESPACE)
      | (1ULL << REmatchParser::WORD_CHAR)
      | (1ULL << REmatchParser::NOT_WORD_CHAR)
      | (1ULL << REmatchParser::VARNAME)
      | (1ULL << REmatchParser::EXCLAMAITON)
      | (1ULL << REmatchParser::L_PAR)
      | (1ULL << REmatchParser::COMMA)
      | (1ULL << REmatchParser::HAT)
      | (1ULL << REmatchParser::HYPHEN)
      | (1ULL << REmatchParser::L_BRACK)
      | (1ULL << REmatchParser::BACKSLASH)
      | (1ULL << REmatchParser::ALPHA)
      | (1ULL << REmatchParser::DIGIT)
      | (1ULL << REmatchParser::UNRECOGNIZED))) != 0));
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ElementContext ------------------------------------------------------------------

REmatchParser::ElementContext::ElementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

REmatchParser::GroupContext* REmatchParser::ElementContext::group() {
  return getRuleContext<REmatchParser::GroupContext>(0);
}

REmatchParser::QuantifierContext* REmatchParser::ElementContext::quantifier() {
  return getRuleContext<REmatchParser::QuantifierContext>(0);
}


size_t REmatchParser::ElementContext::getRuleIndex() const {
  return REmatchParser::RuleElement;
}


std::any REmatchParser::ElementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<REmatchParserVisitor*>(visitor))
    return parserVisitor->visitElement(this);
  else
    return visitor->visitChildren(this);
}

REmatchParser::ElementContext* REmatchParser::element() {
  ElementContext *_localctx = _tracker.createInstance<ElementContext>(_ctx, getState());
  enterRule(_localctx, 6, REmatchParser::RuleElement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(66);
    group();
    setState(68);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << REmatchParser::L_CURLY)
      | (1ULL << REmatchParser::QUESTION)
      | (1ULL << REmatchParser::PLUS)
      | (1ULL << REmatchParser::STAR))) != 0)) {
      setState(67);
      quantifier();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GroupContext ------------------------------------------------------------------

REmatchParser::GroupContext::GroupContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

REmatchParser::ParenthesesContext* REmatchParser::GroupContext::parentheses() {
  return getRuleContext<REmatchParser::ParenthesesContext>(0);
}

REmatchParser::AssignationContext* REmatchParser::GroupContext::assignation() {
  return getRuleContext<REmatchParser::AssignationContext>(0);
}

REmatchParser::AtomContext* REmatchParser::GroupContext::atom() {
  return getRuleContext<REmatchParser::AtomContext>(0);
}


size_t REmatchParser::GroupContext::getRuleIndex() const {
  return REmatchParser::RuleGroup;
}


std::any REmatchParser::GroupContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<REmatchParserVisitor*>(visitor))
    return parserVisitor->visitGroup(this);
  else
    return visitor->visitChildren(this);
}

REmatchParser::GroupContext* REmatchParser::group() {
  GroupContext *_localctx = _tracker.createInstance<GroupContext>(_ctx, getState());
  enterRule(_localctx, 8, REmatchParser::RuleGroup);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(73);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(70);
      parentheses();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(71);
      assignation();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(72);
      atom();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParenthesesContext ------------------------------------------------------------------

REmatchParser::ParenthesesContext::ParenthesesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* REmatchParser::ParenthesesContext::L_PAR() {
  return getToken(REmatchParser::L_PAR, 0);
}

REmatchParser::AlternationContext* REmatchParser::ParenthesesContext::alternation() {
  return getRuleContext<REmatchParser::AlternationContext>(0);
}

tree::TerminalNode* REmatchParser::ParenthesesContext::R_PAR() {
  return getToken(REmatchParser::R_PAR, 0);
}


size_t REmatchParser::ParenthesesContext::getRuleIndex() const {
  return REmatchParser::RuleParentheses;
}


std::any REmatchParser::ParenthesesContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<REmatchParserVisitor*>(visitor))
    return parserVisitor->visitParentheses(this);
  else
    return visitor->visitChildren(this);
}

REmatchParser::ParenthesesContext* REmatchParser::parentheses() {
  ParenthesesContext *_localctx = _tracker.createInstance<ParenthesesContext>(_ctx, getState());
  enterRule(_localctx, 10, REmatchParser::RuleParentheses);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(75);
    match(REmatchParser::L_PAR);
    setState(76);
    alternation();
    setState(77);
    match(REmatchParser::R_PAR);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssignationContext ------------------------------------------------------------------

REmatchParser::AssignationContext::AssignationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* REmatchParser::AssignationContext::EXCLAMAITON() {
  return getToken(REmatchParser::EXCLAMAITON, 0);
}

tree::TerminalNode* REmatchParser::AssignationContext::VARNAME() {
  return getToken(REmatchParser::VARNAME, 0);
}

tree::TerminalNode* REmatchParser::AssignationContext::L_CURLY() {
  return getToken(REmatchParser::L_CURLY, 0);
}

REmatchParser::AlternationContext* REmatchParser::AssignationContext::alternation() {
  return getRuleContext<REmatchParser::AlternationContext>(0);
}

tree::TerminalNode* REmatchParser::AssignationContext::R_CURLY() {
  return getToken(REmatchParser::R_CURLY, 0);
}


size_t REmatchParser::AssignationContext::getRuleIndex() const {
  return REmatchParser::RuleAssignation;
}


std::any REmatchParser::AssignationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<REmatchParserVisitor*>(visitor))
    return parserVisitor->visitAssignation(this);
  else
    return visitor->visitChildren(this);
}

REmatchParser::AssignationContext* REmatchParser::assignation() {
  AssignationContext *_localctx = _tracker.createInstance<AssignationContext>(_ctx, getState());
  enterRule(_localctx, 12, REmatchParser::RuleAssignation);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(79);
    match(REmatchParser::EXCLAMAITON);
    setState(80);
    match(REmatchParser::VARNAME);
    setState(81);
    match(REmatchParser::L_CURLY);
    setState(82);
    alternation();
    setState(83);
    match(REmatchParser::R_CURLY);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AtomContext ------------------------------------------------------------------

REmatchParser::AtomContext::AtomContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

REmatchParser::CharacterClassContext* REmatchParser::AtomContext::characterClass() {
  return getRuleContext<REmatchParser::CharacterClassContext>(0);
}

REmatchParser::SharedAtomContext* REmatchParser::AtomContext::sharedAtom() {
  return getRuleContext<REmatchParser::SharedAtomContext>(0);
}

REmatchParser::LiteralContext* REmatchParser::AtomContext::literal() {
  return getRuleContext<REmatchParser::LiteralContext>(0);
}


size_t REmatchParser::AtomContext::getRuleIndex() const {
  return REmatchParser::RuleAtom;
}


std::any REmatchParser::AtomContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<REmatchParserVisitor*>(visitor))
    return parserVisitor->visitAtom(this);
  else
    return visitor->visitChildren(this);
}

REmatchParser::AtomContext* REmatchParser::atom() {
  AtomContext *_localctx = _tracker.createInstance<AtomContext>(_ctx, getState());
  enterRule(_localctx, 14, REmatchParser::RuleAtom);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(88);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(85);
      characterClass();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(86);
      sharedAtom();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(87);
      literal();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CharacterClassContext ------------------------------------------------------------------

REmatchParser::CharacterClassContext::CharacterClassContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* REmatchParser::CharacterClassContext::L_BRACK() {
  return getToken(REmatchParser::L_BRACK, 0);
}

tree::TerminalNode* REmatchParser::CharacterClassContext::R_BRACK() {
  return getToken(REmatchParser::R_BRACK, 0);
}

tree::TerminalNode* REmatchParser::CharacterClassContext::HAT() {
  return getToken(REmatchParser::HAT, 0);
}

std::vector<REmatchParser::CcAtomContext *> REmatchParser::CharacterClassContext::ccAtom() {
  return getRuleContexts<REmatchParser::CcAtomContext>();
}

REmatchParser::CcAtomContext* REmatchParser::CharacterClassContext::ccAtom(size_t i) {
  return getRuleContext<REmatchParser::CcAtomContext>(i);
}


size_t REmatchParser::CharacterClassContext::getRuleIndex() const {
  return REmatchParser::RuleCharacterClass;
}


std::any REmatchParser::CharacterClassContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<REmatchParserVisitor*>(visitor))
    return parserVisitor->visitCharacterClass(this);
  else
    return visitor->visitChildren(this);
}

REmatchParser::CharacterClassContext* REmatchParser::characterClass() {
  CharacterClassContext *_localctx = _tracker.createInstance<CharacterClassContext>(_ctx, getState());
  enterRule(_localctx, 16, REmatchParser::RuleCharacterClass);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(90);
    match(REmatchParser::L_BRACK);
    setState(92);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
    case 1: {
      setState(91);
      match(REmatchParser::HAT);
      break;
    }

    default:
      break;
    }
    setState(95); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(94);
      ccAtom();
      setState(97); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << REmatchParser::DECIMAL_DIGIT)
      | (1ULL << REmatchParser::NOT_DECIMAL_DIGIT)
      | (1ULL << REmatchParser::HORIZONTAL_WHITESPACE)
      | (1ULL << REmatchParser::NOT_HORIZONTAL_WHITESPACE)
      | (1ULL << REmatchParser::NEW_LINE)
      | (1ULL << REmatchParser::NOT_NEW_LINE)
      | (1ULL << REmatchParser::WHITESPACE)
      | (1ULL << REmatchParser::NOT_WHITESPACE)
      | (1ULL << REmatchParser::VERTICAL_WHITESPACE)
      | (1ULL << REmatchParser::NOT_VERTICAL_WHITESPACE)
      | (1ULL << REmatchParser::WORD_CHAR)
      | (1ULL << REmatchParser::NOT_WORD_CHAR)
      | (1ULL << REmatchParser::VARNAME)
      | (1ULL << REmatchParser::PIPE)
      | (1ULL << REmatchParser::EXCLAMAITON)
      | (1ULL << REmatchParser::L_CURLY)
      | (1ULL << REmatchParser::R_CURLY)
      | (1ULL << REmatchParser::L_PAR)
      | (1ULL << REmatchParser::R_PAR)
      | (1ULL << REmatchParser::COMMA)
      | (1ULL << REmatchParser::QUESTION)
      | (1ULL << REmatchParser::PLUS)
      | (1ULL << REmatchParser::STAR)
      | (1ULL << REmatchParser::HAT)
      | (1ULL << REmatchParser::HYPHEN)
      | (1ULL << REmatchParser::L_BRACK)
      | (1ULL << REmatchParser::BACKSLASH)
      | (1ULL << REmatchParser::ALPHA)
      | (1ULL << REmatchParser::DIGIT)
      | (1ULL << REmatchParser::DOT)
      | (1ULL << REmatchParser::UNRECOGNIZED))) != 0));
    setState(99);
    match(REmatchParser::R_BRACK);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CcAtomContext ------------------------------------------------------------------

REmatchParser::CcAtomContext::CcAtomContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

REmatchParser::CcRangeContext* REmatchParser::CcAtomContext::ccRange() {
  return getRuleContext<REmatchParser::CcRangeContext>(0);
}

REmatchParser::SharedAtomContext* REmatchParser::CcAtomContext::sharedAtom() {
  return getRuleContext<REmatchParser::SharedAtomContext>(0);
}

REmatchParser::LiteralContext* REmatchParser::CcAtomContext::literal() {
  return getRuleContext<REmatchParser::LiteralContext>(0);
}


size_t REmatchParser::CcAtomContext::getRuleIndex() const {
  return REmatchParser::RuleCcAtom;
}


std::any REmatchParser::CcAtomContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<REmatchParserVisitor*>(visitor))
    return parserVisitor->visitCcAtom(this);
  else
    return visitor->visitChildren(this);
}

REmatchParser::CcAtomContext* REmatchParser::ccAtom() {
  CcAtomContext *_localctx = _tracker.createInstance<CcAtomContext>(_ctx, getState());
  enterRule(_localctx, 18, REmatchParser::RuleCcAtom);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(104);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(101);
      ccRange();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(102);
      sharedAtom();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(103);
      literal();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CcRangeContext ------------------------------------------------------------------

REmatchParser::CcRangeContext::CcRangeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<REmatchParser::CcLiteralContext *> REmatchParser::CcRangeContext::ccLiteral() {
  return getRuleContexts<REmatchParser::CcLiteralContext>();
}

REmatchParser::CcLiteralContext* REmatchParser::CcRangeContext::ccLiteral(size_t i) {
  return getRuleContext<REmatchParser::CcLiteralContext>(i);
}

tree::TerminalNode* REmatchParser::CcRangeContext::HYPHEN() {
  return getToken(REmatchParser::HYPHEN, 0);
}


size_t REmatchParser::CcRangeContext::getRuleIndex() const {
  return REmatchParser::RuleCcRange;
}


std::any REmatchParser::CcRangeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<REmatchParserVisitor*>(visitor))
    return parserVisitor->visitCcRange(this);
  else
    return visitor->visitChildren(this);
}

REmatchParser::CcRangeContext* REmatchParser::ccRange() {
  CcRangeContext *_localctx = _tracker.createInstance<CcRangeContext>(_ctx, getState());
  enterRule(_localctx, 20, REmatchParser::RuleCcRange);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(106);
    ccLiteral();
    setState(107);
    match(REmatchParser::HYPHEN);
    setState(108);
    ccLiteral();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CcLiteralContext ------------------------------------------------------------------

REmatchParser::CcLiteralContext::CcLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

REmatchParser::CcEscapesContext* REmatchParser::CcLiteralContext::ccEscapes() {
  return getRuleContext<REmatchParser::CcEscapesContext>(0);
}

REmatchParser::CcOtherContext* REmatchParser::CcLiteralContext::ccOther() {
  return getRuleContext<REmatchParser::CcOtherContext>(0);
}


size_t REmatchParser::CcLiteralContext::getRuleIndex() const {
  return REmatchParser::RuleCcLiteral;
}


std::any REmatchParser::CcLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<REmatchParserVisitor*>(visitor))
    return parserVisitor->visitCcLiteral(this);
  else
    return visitor->visitChildren(this);
}

REmatchParser::CcLiteralContext* REmatchParser::ccLiteral() {
  CcLiteralContext *_localctx = _tracker.createInstance<CcLiteralContext>(_ctx, getState());
  enterRule(_localctx, 22, REmatchParser::RuleCcLiteral);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(112);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case REmatchParser::BACKSLASH: {
        enterOuterAlt(_localctx, 1);
        setState(110);
        ccEscapes();
        break;
      }

      case REmatchParser::DECIMAL_DIGIT:
      case REmatchParser::NOT_DECIMAL_DIGIT:
      case REmatchParser::HORIZONTAL_WHITESPACE:
      case REmatchParser::NOT_HORIZONTAL_WHITESPACE:
      case REmatchParser::NEW_LINE:
      case REmatchParser::NOT_NEW_LINE:
      case REmatchParser::WHITESPACE:
      case REmatchParser::NOT_WHITESPACE:
      case REmatchParser::VERTICAL_WHITESPACE:
      case REmatchParser::NOT_VERTICAL_WHITESPACE:
      case REmatchParser::WORD_CHAR:
      case REmatchParser::NOT_WORD_CHAR:
      case REmatchParser::VARNAME:
      case REmatchParser::PIPE:
      case REmatchParser::EXCLAMAITON:
      case REmatchParser::L_CURLY:
      case REmatchParser::R_CURLY:
      case REmatchParser::L_PAR:
      case REmatchParser::R_PAR:
      case REmatchParser::COMMA:
      case REmatchParser::QUESTION:
      case REmatchParser::PLUS:
      case REmatchParser::STAR:
      case REmatchParser::L_BRACK:
      case REmatchParser::ALPHA:
      case REmatchParser::DIGIT:
      case REmatchParser::DOT:
      case REmatchParser::UNRECOGNIZED: {
        enterOuterAlt(_localctx, 2);
        setState(111);
        ccOther();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CcEscapesContext ------------------------------------------------------------------

REmatchParser::CcEscapesContext::CcEscapesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> REmatchParser::CcEscapesContext::BACKSLASH() {
  return getTokens(REmatchParser::BACKSLASH);
}

tree::TerminalNode* REmatchParser::CcEscapesContext::BACKSLASH(size_t i) {
  return getToken(REmatchParser::BACKSLASH, i);
}

tree::TerminalNode* REmatchParser::CcEscapesContext::HAT() {
  return getToken(REmatchParser::HAT, 0);
}

tree::TerminalNode* REmatchParser::CcEscapesContext::HYPHEN() {
  return getToken(REmatchParser::HYPHEN, 0);
}

tree::TerminalNode* REmatchParser::CcEscapesContext::R_BRACK() {
  return getToken(REmatchParser::R_BRACK, 0);
}


size_t REmatchParser::CcEscapesContext::getRuleIndex() const {
  return REmatchParser::RuleCcEscapes;
}


std::any REmatchParser::CcEscapesContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<REmatchParserVisitor*>(visitor))
    return parserVisitor->visitCcEscapes(this);
  else
    return visitor->visitChildren(this);
}

REmatchParser::CcEscapesContext* REmatchParser::ccEscapes() {
  CcEscapesContext *_localctx = _tracker.createInstance<CcEscapesContext>(_ctx, getState());
  enterRule(_localctx, 24, REmatchParser::RuleCcEscapes);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(114);
    match(REmatchParser::BACKSLASH);
    setState(115);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << REmatchParser::HAT)
      | (1ULL << REmatchParser::HYPHEN)
      | (1ULL << REmatchParser::R_BRACK)
      | (1ULL << REmatchParser::BACKSLASH))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CcOtherContext ------------------------------------------------------------------

REmatchParser::CcOtherContext::CcOtherContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* REmatchParser::CcOtherContext::HAT() {
  return getToken(REmatchParser::HAT, 0);
}

tree::TerminalNode* REmatchParser::CcOtherContext::HYPHEN() {
  return getToken(REmatchParser::HYPHEN, 0);
}

tree::TerminalNode* REmatchParser::CcOtherContext::R_BRACK() {
  return getToken(REmatchParser::R_BRACK, 0);
}

tree::TerminalNode* REmatchParser::CcOtherContext::BACKSLASH() {
  return getToken(REmatchParser::BACKSLASH, 0);
}


size_t REmatchParser::CcOtherContext::getRuleIndex() const {
  return REmatchParser::RuleCcOther;
}


std::any REmatchParser::CcOtherContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<REmatchParserVisitor*>(visitor))
    return parserVisitor->visitCcOther(this);
  else
    return visitor->visitChildren(this);
}

REmatchParser::CcOtherContext* REmatchParser::ccOther() {
  CcOtherContext *_localctx = _tracker.createInstance<CcOtherContext>(_ctx, getState());
  enterRule(_localctx, 26, REmatchParser::RuleCcOther);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(117);
    _la = _input->LA(1);
    if (_la == 0 || _la == Token::EOF || ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << REmatchParser::HAT)
      | (1ULL << REmatchParser::HYPHEN)
      | (1ULL << REmatchParser::R_BRACK)
      | (1ULL << REmatchParser::BACKSLASH))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LiteralContext ------------------------------------------------------------------

REmatchParser::LiteralContext::LiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

REmatchParser::EscapesContext* REmatchParser::LiteralContext::escapes() {
  return getRuleContext<REmatchParser::EscapesContext>(0);
}

REmatchParser::OtherContext* REmatchParser::LiteralContext::other() {
  return getRuleContext<REmatchParser::OtherContext>(0);
}


size_t REmatchParser::LiteralContext::getRuleIndex() const {
  return REmatchParser::RuleLiteral;
}


std::any REmatchParser::LiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<REmatchParserVisitor*>(visitor))
    return parserVisitor->visitLiteral(this);
  else
    return visitor->visitChildren(this);
}

REmatchParser::LiteralContext* REmatchParser::literal() {
  LiteralContext *_localctx = _tracker.createInstance<LiteralContext>(_ctx, getState());
  enterRule(_localctx, 28, REmatchParser::RuleLiteral);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(121);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case REmatchParser::BACKSLASH: {
        enterOuterAlt(_localctx, 1);
        setState(119);
        escapes();
        break;
      }

      case REmatchParser::DECIMAL_DIGIT:
      case REmatchParser::NOT_DECIMAL_DIGIT:
      case REmatchParser::HORIZONTAL_WHITESPACE:
      case REmatchParser::NOT_HORIZONTAL_WHITESPACE:
      case REmatchParser::NEW_LINE:
      case REmatchParser::NOT_NEW_LINE:
      case REmatchParser::WHITESPACE:
      case REmatchParser::NOT_WHITESPACE:
      case REmatchParser::VERTICAL_WHITESPACE:
      case REmatchParser::NOT_VERTICAL_WHITESPACE:
      case REmatchParser::WORD_CHAR:
      case REmatchParser::NOT_WORD_CHAR:
      case REmatchParser::VARNAME:
      case REmatchParser::EXCLAMAITON:
      case REmatchParser::COMMA:
      case REmatchParser::HAT:
      case REmatchParser::HYPHEN:
      case REmatchParser::ALPHA:
      case REmatchParser::DIGIT:
      case REmatchParser::UNRECOGNIZED: {
        enterOuterAlt(_localctx, 2);
        setState(120);
        other();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EscapesContext ------------------------------------------------------------------

REmatchParser::EscapesContext::EscapesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> REmatchParser::EscapesContext::BACKSLASH() {
  return getTokens(REmatchParser::BACKSLASH);
}

tree::TerminalNode* REmatchParser::EscapesContext::BACKSLASH(size_t i) {
  return getToken(REmatchParser::BACKSLASH, i);
}

tree::TerminalNode* REmatchParser::EscapesContext::L_BRACK() {
  return getToken(REmatchParser::L_BRACK, 0);
}

tree::TerminalNode* REmatchParser::EscapesContext::R_BRACK() {
  return getToken(REmatchParser::R_BRACK, 0);
}

tree::TerminalNode* REmatchParser::EscapesContext::L_PAR() {
  return getToken(REmatchParser::L_PAR, 0);
}

tree::TerminalNode* REmatchParser::EscapesContext::R_PAR() {
  return getToken(REmatchParser::R_PAR, 0);
}

tree::TerminalNode* REmatchParser::EscapesContext::L_CURLY() {
  return getToken(REmatchParser::L_CURLY, 0);
}

tree::TerminalNode* REmatchParser::EscapesContext::R_CURLY() {
  return getToken(REmatchParser::R_CURLY, 0);
}

tree::TerminalNode* REmatchParser::EscapesContext::STAR() {
  return getToken(REmatchParser::STAR, 0);
}

tree::TerminalNode* REmatchParser::EscapesContext::PLUS() {
  return getToken(REmatchParser::PLUS, 0);
}

tree::TerminalNode* REmatchParser::EscapesContext::QUESTION() {
  return getToken(REmatchParser::QUESTION, 0);
}

tree::TerminalNode* REmatchParser::EscapesContext::PIPE() {
  return getToken(REmatchParser::PIPE, 0);
}

tree::TerminalNode* REmatchParser::EscapesContext::DOT() {
  return getToken(REmatchParser::DOT, 0);
}


size_t REmatchParser::EscapesContext::getRuleIndex() const {
  return REmatchParser::RuleEscapes;
}


std::any REmatchParser::EscapesContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<REmatchParserVisitor*>(visitor))
    return parserVisitor->visitEscapes(this);
  else
    return visitor->visitChildren(this);
}

REmatchParser::EscapesContext* REmatchParser::escapes() {
  EscapesContext *_localctx = _tracker.createInstance<EscapesContext>(_ctx, getState());
  enterRule(_localctx, 30, REmatchParser::RuleEscapes);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(123);
    match(REmatchParser::BACKSLASH);
    setState(124);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << REmatchParser::PIPE)
      | (1ULL << REmatchParser::L_CURLY)
      | (1ULL << REmatchParser::R_CURLY)
      | (1ULL << REmatchParser::L_PAR)
      | (1ULL << REmatchParser::R_PAR)
      | (1ULL << REmatchParser::QUESTION)
      | (1ULL << REmatchParser::PLUS)
      | (1ULL << REmatchParser::STAR)
      | (1ULL << REmatchParser::L_BRACK)
      | (1ULL << REmatchParser::R_BRACK)
      | (1ULL << REmatchParser::BACKSLASH)
      | (1ULL << REmatchParser::DOT))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OtherContext ------------------------------------------------------------------

REmatchParser::OtherContext::OtherContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* REmatchParser::OtherContext::L_BRACK() {
  return getToken(REmatchParser::L_BRACK, 0);
}

tree::TerminalNode* REmatchParser::OtherContext::R_BRACK() {
  return getToken(REmatchParser::R_BRACK, 0);
}

tree::TerminalNode* REmatchParser::OtherContext::L_PAR() {
  return getToken(REmatchParser::L_PAR, 0);
}

tree::TerminalNode* REmatchParser::OtherContext::R_PAR() {
  return getToken(REmatchParser::R_PAR, 0);
}

tree::TerminalNode* REmatchParser::OtherContext::L_CURLY() {
  return getToken(REmatchParser::L_CURLY, 0);
}

tree::TerminalNode* REmatchParser::OtherContext::R_CURLY() {
  return getToken(REmatchParser::R_CURLY, 0);
}

tree::TerminalNode* REmatchParser::OtherContext::STAR() {
  return getToken(REmatchParser::STAR, 0);
}

tree::TerminalNode* REmatchParser::OtherContext::PLUS() {
  return getToken(REmatchParser::PLUS, 0);
}

tree::TerminalNode* REmatchParser::OtherContext::QUESTION() {
  return getToken(REmatchParser::QUESTION, 0);
}

tree::TerminalNode* REmatchParser::OtherContext::PIPE() {
  return getToken(REmatchParser::PIPE, 0);
}

tree::TerminalNode* REmatchParser::OtherContext::DOT() {
  return getToken(REmatchParser::DOT, 0);
}

tree::TerminalNode* REmatchParser::OtherContext::BACKSLASH() {
  return getToken(REmatchParser::BACKSLASH, 0);
}


size_t REmatchParser::OtherContext::getRuleIndex() const {
  return REmatchParser::RuleOther;
}


std::any REmatchParser::OtherContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<REmatchParserVisitor*>(visitor))
    return parserVisitor->visitOther(this);
  else
    return visitor->visitChildren(this);
}

REmatchParser::OtherContext* REmatchParser::other() {
  OtherContext *_localctx = _tracker.createInstance<OtherContext>(_ctx, getState());
  enterRule(_localctx, 32, REmatchParser::RuleOther);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(126);
    _la = _input->LA(1);
    if (_la == 0 || _la == Token::EOF || ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << REmatchParser::PIPE)
      | (1ULL << REmatchParser::L_CURLY)
      | (1ULL << REmatchParser::R_CURLY)
      | (1ULL << REmatchParser::L_PAR)
      | (1ULL << REmatchParser::R_PAR)
      | (1ULL << REmatchParser::QUESTION)
      | (1ULL << REmatchParser::PLUS)
      | (1ULL << REmatchParser::STAR)
      | (1ULL << REmatchParser::L_BRACK)
      | (1ULL << REmatchParser::R_BRACK)
      | (1ULL << REmatchParser::BACKSLASH)
      | (1ULL << REmatchParser::DOT))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SharedAtomContext ------------------------------------------------------------------

REmatchParser::SharedAtomContext::SharedAtomContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* REmatchParser::SharedAtomContext::DECIMAL_DIGIT() {
  return getToken(REmatchParser::DECIMAL_DIGIT, 0);
}

tree::TerminalNode* REmatchParser::SharedAtomContext::NOT_DECIMAL_DIGIT() {
  return getToken(REmatchParser::NOT_DECIMAL_DIGIT, 0);
}

tree::TerminalNode* REmatchParser::SharedAtomContext::HORIZONTAL_WHITESPACE() {
  return getToken(REmatchParser::HORIZONTAL_WHITESPACE, 0);
}

tree::TerminalNode* REmatchParser::SharedAtomContext::NOT_HORIZONTAL_WHITESPACE() {
  return getToken(REmatchParser::NOT_HORIZONTAL_WHITESPACE, 0);
}

tree::TerminalNode* REmatchParser::SharedAtomContext::NEW_LINE() {
  return getToken(REmatchParser::NEW_LINE, 0);
}

tree::TerminalNode* REmatchParser::SharedAtomContext::NOT_NEW_LINE() {
  return getToken(REmatchParser::NOT_NEW_LINE, 0);
}

tree::TerminalNode* REmatchParser::SharedAtomContext::WHITESPACE() {
  return getToken(REmatchParser::WHITESPACE, 0);
}

tree::TerminalNode* REmatchParser::SharedAtomContext::NOT_WHITESPACE() {
  return getToken(REmatchParser::NOT_WHITESPACE, 0);
}

tree::TerminalNode* REmatchParser::SharedAtomContext::VERTICAL_WHITESPACE() {
  return getToken(REmatchParser::VERTICAL_WHITESPACE, 0);
}

tree::TerminalNode* REmatchParser::SharedAtomContext::NOT_VERTICAL_WHITESPACE() {
  return getToken(REmatchParser::NOT_VERTICAL_WHITESPACE, 0);
}

tree::TerminalNode* REmatchParser::SharedAtomContext::WORD_CHAR() {
  return getToken(REmatchParser::WORD_CHAR, 0);
}

tree::TerminalNode* REmatchParser::SharedAtomContext::NOT_WORD_CHAR() {
  return getToken(REmatchParser::NOT_WORD_CHAR, 0);
}


size_t REmatchParser::SharedAtomContext::getRuleIndex() const {
  return REmatchParser::RuleSharedAtom;
}


std::any REmatchParser::SharedAtomContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<REmatchParserVisitor*>(visitor))
    return parserVisitor->visitSharedAtom(this);
  else
    return visitor->visitChildren(this);
}

REmatchParser::SharedAtomContext* REmatchParser::sharedAtom() {
  SharedAtomContext *_localctx = _tracker.createInstance<SharedAtomContext>(_ctx, getState());
  enterRule(_localctx, 34, REmatchParser::RuleSharedAtom);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(128);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << REmatchParser::DECIMAL_DIGIT)
      | (1ULL << REmatchParser::NOT_DECIMAL_DIGIT)
      | (1ULL << REmatchParser::HORIZONTAL_WHITESPACE)
      | (1ULL << REmatchParser::NOT_HORIZONTAL_WHITESPACE)
      | (1ULL << REmatchParser::NEW_LINE)
      | (1ULL << REmatchParser::NOT_NEW_LINE)
      | (1ULL << REmatchParser::WHITESPACE)
      | (1ULL << REmatchParser::NOT_WHITESPACE)
      | (1ULL << REmatchParser::VERTICAL_WHITESPACE)
      | (1ULL << REmatchParser::NOT_VERTICAL_WHITESPACE)
      | (1ULL << REmatchParser::WORD_CHAR)
      | (1ULL << REmatchParser::NOT_WORD_CHAR))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- QuantifierContext ------------------------------------------------------------------

REmatchParser::QuantifierContext::QuantifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* REmatchParser::QuantifierContext::QUESTION() {
  return getToken(REmatchParser::QUESTION, 0);
}

tree::TerminalNode* REmatchParser::QuantifierContext::PLUS() {
  return getToken(REmatchParser::PLUS, 0);
}

tree::TerminalNode* REmatchParser::QuantifierContext::STAR() {
  return getToken(REmatchParser::STAR, 0);
}

tree::TerminalNode* REmatchParser::QuantifierContext::L_CURLY() {
  return getToken(REmatchParser::L_CURLY, 0);
}

REmatchParser::QuantityContext* REmatchParser::QuantifierContext::quantity() {
  return getRuleContext<REmatchParser::QuantityContext>(0);
}

tree::TerminalNode* REmatchParser::QuantifierContext::R_CURLY() {
  return getToken(REmatchParser::R_CURLY, 0);
}


size_t REmatchParser::QuantifierContext::getRuleIndex() const {
  return REmatchParser::RuleQuantifier;
}


std::any REmatchParser::QuantifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<REmatchParserVisitor*>(visitor))
    return parserVisitor->visitQuantifier(this);
  else
    return visitor->visitChildren(this);
}

REmatchParser::QuantifierContext* REmatchParser::quantifier() {
  QuantifierContext *_localctx = _tracker.createInstance<QuantifierContext>(_ctx, getState());
  enterRule(_localctx, 36, REmatchParser::RuleQuantifier);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(137);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case REmatchParser::QUESTION: {
        enterOuterAlt(_localctx, 1);
        setState(130);
        match(REmatchParser::QUESTION);
        break;
      }

      case REmatchParser::PLUS: {
        enterOuterAlt(_localctx, 2);
        setState(131);
        match(REmatchParser::PLUS);
        break;
      }

      case REmatchParser::STAR: {
        enterOuterAlt(_localctx, 3);
        setState(132);
        match(REmatchParser::STAR);
        break;
      }

      case REmatchParser::L_CURLY: {
        enterOuterAlt(_localctx, 4);
        setState(133);
        match(REmatchParser::L_CURLY);
        setState(134);
        quantity();
        setState(135);
        match(REmatchParser::R_CURLY);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- QuantityContext ------------------------------------------------------------------

REmatchParser::QuantityContext::QuantityContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

REmatchParser::QuantExactContext* REmatchParser::QuantityContext::quantExact() {
  return getRuleContext<REmatchParser::QuantExactContext>(0);
}

REmatchParser::QuantRangeContext* REmatchParser::QuantityContext::quantRange() {
  return getRuleContext<REmatchParser::QuantRangeContext>(0);
}

REmatchParser::QuantMinContext* REmatchParser::QuantityContext::quantMin() {
  return getRuleContext<REmatchParser::QuantMinContext>(0);
}

REmatchParser::QuantMaxContext* REmatchParser::QuantityContext::quantMax() {
  return getRuleContext<REmatchParser::QuantMaxContext>(0);
}


size_t REmatchParser::QuantityContext::getRuleIndex() const {
  return REmatchParser::RuleQuantity;
}


std::any REmatchParser::QuantityContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<REmatchParserVisitor*>(visitor))
    return parserVisitor->visitQuantity(this);
  else
    return visitor->visitChildren(this);
}

REmatchParser::QuantityContext* REmatchParser::quantity() {
  QuantityContext *_localctx = _tracker.createInstance<QuantityContext>(_ctx, getState());
  enterRule(_localctx, 38, REmatchParser::RuleQuantity);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(143);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(139);
      quantExact();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(140);
      quantRange();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(141);
      quantMin();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(142);
      quantMax();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- QuantExactContext ------------------------------------------------------------------

REmatchParser::QuantExactContext::QuantExactContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

REmatchParser::NumberContext* REmatchParser::QuantExactContext::number() {
  return getRuleContext<REmatchParser::NumberContext>(0);
}


size_t REmatchParser::QuantExactContext::getRuleIndex() const {
  return REmatchParser::RuleQuantExact;
}


std::any REmatchParser::QuantExactContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<REmatchParserVisitor*>(visitor))
    return parserVisitor->visitQuantExact(this);
  else
    return visitor->visitChildren(this);
}

REmatchParser::QuantExactContext* REmatchParser::quantExact() {
  QuantExactContext *_localctx = _tracker.createInstance<QuantExactContext>(_ctx, getState());
  enterRule(_localctx, 40, REmatchParser::RuleQuantExact);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(145);
    number();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- QuantRangeContext ------------------------------------------------------------------

REmatchParser::QuantRangeContext::QuantRangeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<REmatchParser::NumberContext *> REmatchParser::QuantRangeContext::number() {
  return getRuleContexts<REmatchParser::NumberContext>();
}

REmatchParser::NumberContext* REmatchParser::QuantRangeContext::number(size_t i) {
  return getRuleContext<REmatchParser::NumberContext>(i);
}

tree::TerminalNode* REmatchParser::QuantRangeContext::COMMA() {
  return getToken(REmatchParser::COMMA, 0);
}


size_t REmatchParser::QuantRangeContext::getRuleIndex() const {
  return REmatchParser::RuleQuantRange;
}


std::any REmatchParser::QuantRangeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<REmatchParserVisitor*>(visitor))
    return parserVisitor->visitQuantRange(this);
  else
    return visitor->visitChildren(this);
}

REmatchParser::QuantRangeContext* REmatchParser::quantRange() {
  QuantRangeContext *_localctx = _tracker.createInstance<QuantRangeContext>(_ctx, getState());
  enterRule(_localctx, 42, REmatchParser::RuleQuantRange);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(147);
    number();
    setState(148);
    match(REmatchParser::COMMA);
    setState(149);
    number();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- QuantMinContext ------------------------------------------------------------------

REmatchParser::QuantMinContext::QuantMinContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

REmatchParser::NumberContext* REmatchParser::QuantMinContext::number() {
  return getRuleContext<REmatchParser::NumberContext>(0);
}

tree::TerminalNode* REmatchParser::QuantMinContext::COMMA() {
  return getToken(REmatchParser::COMMA, 0);
}


size_t REmatchParser::QuantMinContext::getRuleIndex() const {
  return REmatchParser::RuleQuantMin;
}


std::any REmatchParser::QuantMinContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<REmatchParserVisitor*>(visitor))
    return parserVisitor->visitQuantMin(this);
  else
    return visitor->visitChildren(this);
}

REmatchParser::QuantMinContext* REmatchParser::quantMin() {
  QuantMinContext *_localctx = _tracker.createInstance<QuantMinContext>(_ctx, getState());
  enterRule(_localctx, 44, REmatchParser::RuleQuantMin);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(151);
    number();
    setState(152);
    match(REmatchParser::COMMA);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- QuantMaxContext ------------------------------------------------------------------

REmatchParser::QuantMaxContext::QuantMaxContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* REmatchParser::QuantMaxContext::COMMA() {
  return getToken(REmatchParser::COMMA, 0);
}

REmatchParser::NumberContext* REmatchParser::QuantMaxContext::number() {
  return getRuleContext<REmatchParser::NumberContext>(0);
}


size_t REmatchParser::QuantMaxContext::getRuleIndex() const {
  return REmatchParser::RuleQuantMax;
}


std::any REmatchParser::QuantMaxContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<REmatchParserVisitor*>(visitor))
    return parserVisitor->visitQuantMax(this);
  else
    return visitor->visitChildren(this);
}

REmatchParser::QuantMaxContext* REmatchParser::quantMax() {
  QuantMaxContext *_localctx = _tracker.createInstance<QuantMaxContext>(_ctx, getState());
  enterRule(_localctx, 46, REmatchParser::RuleQuantMax);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(154);
    match(REmatchParser::COMMA);
    setState(155);
    number();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NumberContext ------------------------------------------------------------------

REmatchParser::NumberContext::NumberContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> REmatchParser::NumberContext::DIGIT() {
  return getTokens(REmatchParser::DIGIT);
}

tree::TerminalNode* REmatchParser::NumberContext::DIGIT(size_t i) {
  return getToken(REmatchParser::DIGIT, i);
}


size_t REmatchParser::NumberContext::getRuleIndex() const {
  return REmatchParser::RuleNumber;
}


std::any REmatchParser::NumberContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<REmatchParserVisitor*>(visitor))
    return parserVisitor->visitNumber(this);
  else
    return visitor->visitChildren(this);
}

REmatchParser::NumberContext* REmatchParser::number() {
  NumberContext *_localctx = _tracker.createInstance<NumberContext>(_ctx, getState());
  enterRule(_localctx, 48, REmatchParser::RuleNumber);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(158); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(157);
      match(REmatchParser::DIGIT);
      setState(160); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == REmatchParser::DIGIT);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

void REmatchParser::initialize() {
  std::call_once(rematchparserParserOnceFlag, rematchparserParserInitialize);
}
