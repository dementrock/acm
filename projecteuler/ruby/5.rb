require 'prime'
h = Hash.new(0)
(1..20).each { |x|
  Prime.prime_division(x).each { |x, y|
    h[x] = h[x] < y ? y : h[x]
  }
}
puts Prime.int_from_prime_division(h.to_a)
