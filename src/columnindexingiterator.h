#ifndef COLUMN_INDEXING_ITERATOR_H
#define COLUMN_INDEXING_ITERATOR_H

#include "graycodes.h"

class ColumnIndexingScheme;

class ColumnIndexingIterator {
private:
  const ColumnIndexingScheme* parent;
  GrayCodes* graycodes;
  unsigned int index;
  unsigned int forward_projection;
  unsigned int forward_dual_projection; // the dual of the forward projection

public:
  ColumnIndexingIterator(const ColumnIndexingScheme* parent);
  virtual ~ColumnIndexingIterator();
  
  bool has_next();
  
  // mt 
   ColumnIndexingIterator():parent(NULL),graycodes(NULL) {}
  int get_length() const;
  unsigned int compute_forward_projection();
  void advance_idx(int *bit_changed, const int idx);
  void reset(const ColumnIndexingScheme*);

  /** Move to next index (i.e. DP table row).  
   *
   *  @param bit_changed If not null, and only one bit in the
   *  partitioning (as retrieved by get_partition) is changed by this
   *  call to advance, then the index of this bit is written to the
   *  referenced variable; if not, -1 is written.
   */
  void advance(int* bit_changed = 0);
  
  /** Index of the projection of the current read set onto the intersection between current and next read set. */
  unsigned int get_forward_projection();

  /** Index of the dual of the forward projection (above) */
  unsigned int get_forward_dual_projection();

  /** Index of the projection of the current read set onto the intersection between previous and the current read set. */
  unsigned int get_backward_projection();

  /** Row index in the DP table (within the current column). */
  unsigned int get_index();

  /** Bit-wise representation of the partitioning corresponding to the current index. */
  unsigned int get_partition();

  // used in the backtracking

  /** get index's backward projection (given index i), so that we don't have to iterate up to it, just to get it */
  unsigned int index_backward_projection(unsigned int i);

  // used in the backtracking in the HALF_TABLE case

  /** get index's dual's backward projection (see above) */
  unsigned int dual_index_backward_projection(unsigned int i);

  /** get index's dual */
  unsigned int dual_index(unsigned int i);

  /** get index's dual's forward projection (see above) */
  unsigned int index_forward_projection(unsigned int i);

};

#endif
