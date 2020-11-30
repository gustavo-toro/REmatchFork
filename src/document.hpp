#ifndef DOCUMENT_HPP
#define DOCUMENT_HPP

#include <string>
#include <istream>
#include <string_view>
#include <cstring>

#include <utf8.h>

class Document {
 public:
  using value_t = char;
  using ptr = char*;
  using const_ptr = const char32_t*;
  using ref = char32_t&;
  using const_ref = const char&;
  using const_iterator = const char32_t*;
  using iterator = Document::const_iterator;
  using sz_t = size_t;

  virtual void get(ref c) = 0;
  virtual void reset() = 0;
  virtual sz_t size() const = 0;
  virtual bool getline(std::string &str) = 0;

  virtual ~Document() = default;
}; // end class Document


class StrDocument : public Document {

 public:
  StrDocument()
      : data_(nullptr), size_(0), current_(0) {}

  StrDocument(const std::string &str)
      : size_(0), current_(0) {
    utf8::utf8to32(str.begin(), str.end(),std::back_inserter(data_));
    size_ = data_.size();
  }

  virtual ~StrDocument() = default;

  Document::const_iterator begin() const {return &data_[0];}
  Document::const_iterator end() const {return &data_[0] + size_;}

  virtual Document::sz_t size() const {return size_;}

  virtual void get(Document::ref c) {
    // std::cout << "[StrDoc] get() arg is '" << c << "'\n";
    // std::cout << "[StrDoc] Check stored data:";
    //   for(size_t i = 0; i < size_; i++) {
    //     std::cout << "'" << data_[i] << "' ";
    //   }
    // std::cout << std::endl;
    c = data_[current_];
    // std::cout << "[StrDoc] Checking data_[current_]: '" << data_[current_] << "'\n";
    // if(current_ < size_)
      // std::cout << "[StrDoc] Checking next data_[current_]: '" << data_[current_+1] << "'\n";
    current_++;
  }

  virtual bool getline(std::string &str) {
      if(current_ == size_) return false;
      Document::const_ptr result = std::find(&data_[current_], &data_[0] + size_, '\n');
      std::memcpy(&str[0], &data_[current_], result - &data_[current_]);
      return true;
  }

  virtual void reset() {current_ = 0;}

 private:
    std::u32string data_;
    Document::sz_t size_;
    Document::sz_t current_;

}; // end class StrDocument


// class FileDocument : public Document {
//  public:
//   FileDocument()
//       : data_(nullptr), size_(0) {}

//   FileDocument(std::istream &is)
//       : data_(&is) {
//     }

// 	virtual ~FileDocument() = default;

//   virtual Document::sz_t size() const {return size_;}

//   virtual void get(Document::ref c) {data_->get(c);}

//   virtual bool getline(std::string &str) {
//       return !std::getline(*data_ ,str).eof();
//   }

//   virtual void reset() {data_->seekg(0);}



//  private:
//     std::istream *data_;
//     Document::sz_t size_;

// }; // end class StrDocument

#endif // DOCUMENT_HPP