#ifndef OPTIONS_HPP
#define OPTIONS_HPP

namespace rematch {

enum OutputOption { BENCHMARK, SUBMATCHES, SPANS, NMAPPINGS, DEBUG };

enum InputOption { RGXSTR, RGXFILE, NFAFILE };

// Evaluation options
class Options {
public:
  // The options are (defaults in parenthesis):
  //
  //  output_option   (SPANS)     how to format the output
  //  input_option    (RGXFILE)   how to interpret input string
  //  line_by_line    (false)     looks for matches in the span of a single
  //  line. capturing       (true)      activate capturing. early_output (false)
  //  output a result as soon as it's available..
  //
  Options()
      : output_option_(SPANS), input_option_(RGXFILE), line_by_line_(false),
        capturing_(true), early_output_(false), is_docfile_(false),
        searching_(false), macrodfa_(false) {}

  // Getters and setters

  OutputOption output_option() const { return output_option_; }
  void set_output_option(OutputOption o) { output_option_ = o; }

  InputOption input_option() const { return input_option_; }
  void set_input_option(InputOption i) { input_option_ = i; }

  bool line_by_line() const { return line_by_line_; }
  void set_line_by_line(bool b) { line_by_line_ = b; }

  bool capturing() const { return capturing_; }
  void set_capturing(bool b) { capturing_ = b; }

  bool early_output() const { return early_output_; }
  void set_early_output(bool b) { early_output_ = b; }

  bool is_docfile() const { return is_docfile_; }
  void set_is_docfile(bool b) { is_docfile_ = b; }

  bool searching() const { return searching_; }
  void set_searching(bool b) { searching_ = b; }

  bool macrodfa() const { return macrodfa_; }
  void set_macrodfa(bool b) { macrodfa_ = b; }

private:
  OutputOption output_option_;
  InputOption input_option_;
  bool line_by_line_;
  bool capturing_;
  bool early_output_;
  bool is_docfile_;
  bool searching_;
  bool macrodfa_;

}; // class Options

} // namespace rematch

#endif // OPTIONS_HPP