#ifndef REGEX__REGEX_OPTIONS_HPP
#define REGEX__REGEX_OPTIONS_HPP

namespace rematch {

class RegExOptions {
 public:
  RegExOptions() = default;

  bool multi_line() const {return multi_line_;}
  void set_multi_line(bool b) {multi_line_ = b;}

  bool line_by_line() const {return line_by_line_;}
  void set_line_by_line(bool b) {line_by_line_ = b;}

  bool dot_nl() const {return dot_nl_;}
  void set_dot_nl(bool b) {dot_nl_ = b;}

  bool start_anchor() const {return start_anchor_;}
  void set_start_anchor(bool b) {start_anchor_ = b;}

  bool end_anchor() const {return end_anchor_;}
  void set_end_anchor(bool b) {end_anchor_ = b;}

  bool early_output() const {return early_output_;}
  void set_early_output(bool b) {early_output_ = b;}

  bool save_anchors() const {return save_anchors_;}
  void set_save_anchors(bool b) {save_anchors_ = b;}

  bool ranked() const { return ranked_; }
  void set_ranked(bool b) { ranked_ = b; }

  bool do_cross_product() const { return do_cross_product_; }
  void set_do_cross_product(bool b) { do_cross_product_ = b; }

 private:

  bool multi_line_        = false;
  bool line_by_line_      = false;
  bool dot_nl_            = false;
  bool start_anchor_      = false;
  bool end_anchor_        = false;
  bool early_output_      = false;
  bool save_anchors_      = false;
  bool ranked_            = false; // Ranked enumeration
  bool do_cross_product_  = true;
}; // end class RegExOptions

} // end namespace rematch

#endif // REGEX__REGEX_OPTIONS_HPP