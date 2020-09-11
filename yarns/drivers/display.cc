// Copyright 2013 Emilie Gillet.
//
// Author: Emilie Gillet (emilie.o.gillet@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
// 
// See http://creativecommons.org/licenses/MIT/ for more information.
//
// -----------------------------------------------------------------------------
//
// Driver for 4x14-segments display.

#include "yarns/drivers/display.h"

#include <stm32f10x_conf.h>
#include <string.h>

#include "yarns/resources.h"

namespace yarns {

const uint16_t kPinClk = GPIO_Pin_7;
const uint16_t kPinEnable = GPIO_Pin_8;
const uint16_t kPinData = GPIO_Pin_9;

const uint16_t kScrollingDelay = 180;
const uint16_t kScrollingPreDelay = 1500;
const uint16_t kBlinkMask = 128;

const uint16_t kCharacterEnablePins[] = {
  GPIO_Pin_6,
  GPIO_Pin_5
};

void Display::Init() {

}

void Display::Scroll() {
}

void Display::RefreshSlow() {
#ifdef APPLICATION
  if (scrolling_) {
    if (scrolling_pre_delay_timer_) {
      --scrolling_pre_delay_timer_;
    } else {
      --scrolling_timer_;
      if (scrolling_timer_ == 0) {
        ++scrolling_step_;
        if (scrolling_step_ > long_buffer_size_ - kDisplayWidth + 1) {
          scrolling_ = false;
        }
        scrolling_timer_ = kScrollingDelay;
      }
    }
  }

  displayed_buffer_ = (scrolling_ && !scrolling_pre_delay_timer_)
      ? long_buffer_ + scrolling_step_
      : short_buffer_;

  if (fading_increment_) {
    fading_counter_ += fading_increment_;
  }
  
  uint8_t brightness = brightness_;
  if (fading_increment_) {
    brightness = fading_counter_ < 0x8000
        ? fading_counter_ >> 12
        : 15 - (fading_counter_ >> 12);
  }
  actual_brightness_ = brightness >> 1;
  blink_counter_ = (blink_counter_ + 1) % (kBlinkMask * 2);

#else

  displayed_buffer_ = short_buffer_;
  actual_brightness_ = 3;

#endif  // APPLICATION
}

void Display::RefreshFast() {
 
}

void Display::Print(const char* short_buffer, const char* long_buffer) {

}


void Display::Shift14SegmentsWord(uint16_t data) {
  
}

}  // namespace yarns
