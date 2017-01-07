#pragma once

// This file is part of the Marian toolkit.
// Marian is copyright (c) 2016 Marcin Junczys-Dowmunt.
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
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <functional>
#include <random>
#include "tensors/tensor.h"
#include "cnpy/cnpy.h"

namespace marian {

float xor128();

// Use a constant seed for deterministic behaviour.
//std::default_random_engine engine(42);

void zeros(Tensor t);

void ones(Tensor t);

std::function<void(Tensor)> from_value(float v);

std::function<void(Tensor)> diag(float val);


template <class Distribution>
void distribution(Tensor t, float a, float b) {
  std::random_device device;
  std::default_random_engine engine(device());
  Distribution dist(a, b);
  auto gen = std::bind(dist, engine);

  std::vector<float> vals(t->size());
  std::generate(begin(vals), end(vals), gen);

  t << vals;
}

std::function<void(Tensor)> normal(float mean = 0.0, float std = 0.05);

std::function<void(Tensor)> uniform(float a = -0.05, float b = 0.05);

void glorot_uniform(Tensor t);

void xorshift(Tensor t);

void glorot_normal(Tensor t);

std::function<void(Tensor)> from_vector(const std::vector<float>& v);

std::function<void(Tensor)> from_numpy(const cnpy::NpyArray& np);


} // namespace marian
