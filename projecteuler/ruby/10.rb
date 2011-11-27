require 'prime'
sum = 0
Prime.each(2000000) { |x| sum += x }
puts sum
