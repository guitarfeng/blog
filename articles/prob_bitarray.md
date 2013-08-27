Bit Array
=====================
k*w bits in total.

<pre class="prettyprint"> 
for i from 0 to n/w-1
   complement_a[i] := not a[i] 
   union[i]        := a[i] or b[i] 
   intersection[i] := a[i] and b[i]
   difference[i]   := a[i] and (not b[i])

for i from 0 to n/w-1 
    index := 0    // if needed
    word := a[i]
    for b from 0 to w-1
        value := word and 1 ≠ 0
        word := word shift right 1 
        // do something with value 
        index := index + 1 // if needed
</pre> 
