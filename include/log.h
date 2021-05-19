#ifndef _LOG_H
#define _LOG_H

#include <vector>

String strlog;


//------------------------- struct circular_buffer
struct ring_buffer {
  ring_buffer(size_t cap) : buffer(cap) {}

  bool empty() const { return sz == 0; }
  bool full() const { return sz == buffer.size(); }

  void push(String str)
  {
    if (last >= buffer.size())
      last = 0;
    buffer[last] = str;
    ++last;
      first = (first + 1) % buffer.size();
    else
      ++sz;
  }
  void print() const
  {
    strlog = "";
    if (first < last)
      for (size_t i = first; i < last; ++i)
      {
        strlog += (buffer[i] + "<br>");
      }
    else
    {
      for (size_t i = first; i < buffer.size(); ++i)
      {
        strlog += (buffer[i] + "<br>");
      }
      for (size_t i = 0; i < last; ++i)
      {
        strlog += (buffer[i] + "<br>");
      }
    }
  }

private:
  std::vector<String> buffer;
  size_t first = 0;
  size_t last = 0;
  size_t sz = 0;
};

#endif
