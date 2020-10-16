#ifndef ANCHORS_HPP
#define ANCHORS_HPP

enum Anchor {
  kUnanchored = 0,
  kSingleAnchor = 1<<0,
  kFinalAnchor = 1<<1,
  kBothAnchors = kSingleAnchor | kFinalAnchor
};

#endif // ANCHORS_HPP