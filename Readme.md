# DutyRoll

Parallel C++ implementation allowing computation of rolling duty cycle at various thresholds.

## Installation

```
pip install dutyroll
```

## Building

```
python setup.py build [bdist_wheel | install]
```

## Examples

```
import numpy as np
from dutyroll import rollduty

time = np.array([0, 1, 2.5, 2.6, 2.9, 5.4, 6, 6.1, 7, 12, 13, 13.1])
data = np.array([0.1, 0.2, 0.1, 0.4, 0.5, 0.6, 0.4, 0.7, 0.3, 0.8, 0.9, 0.1])
thresholds = np.linspace(start=0, stop=1, num=21)

# Using a three-sample rolling window:
rollduty(data, 3, thresholds)

# Using a two-second rolling window:
rollduty(time, data, 2, thresholds)
```

The three-sample rolling window call would return:

```
array([[  nan,   nan, 1.   , 1.   , 1.   , 1.   , 1.   , 1.   , 1.   , 1.   , 1.   , 1.   ],
       [  nan,   nan, 1.   , 1.   , 1.   , 1.   , 1.   , 1.   , 1.   , 1.   , 1.   , 1.   ],
       [  nan,   nan, 1.   , 1.   , 1.   , 1.   , 1.   , 1.   , 1.   , 1.   , 1.   , 1.   ],
       [  nan,   nan, 0.333, 0.667, 0.667, 1.   , 1.   , 1.   , 1.   , 1.   , 1.   , 0.667],
       [  nan,   nan, 0.333, 0.667, 0.667, 1.   , 1.   , 1.   , 1.   , 1.   , 1.   , 0.667],
       [  nan,   nan, 0.   , 0.333, 0.667, 1.   , 1.   , 1.   , 1.   , 1.   , 1.   , 0.667],
       [  nan,   nan, 0.   , 0.333, 0.667, 1.   , 1.   , 1.   , 0.667, 0.667, 0.667, 0.667],
       [  nan,   nan, 0.   , 0.333, 0.667, 1.   , 1.   , 1.   , 0.667, 0.667, 0.667, 0.667],
       [  nan,   nan, 0.   , 0.333, 0.667, 1.   , 1.   , 1.   , 0.667, 0.667, 0.667, 0.667],
       [  nan,   nan, 0.   , 0.   , 0.333, 0.667, 0.667, 0.667, 0.333, 0.667, 0.667, 0.667],
       [  nan,   nan, 0.   , 0.   , 0.333, 0.667, 0.667, 0.667, 0.333, 0.667, 0.667, 0.667],
       [  nan,   nan, 0.   , 0.   , 0.   , 0.333, 0.333, 0.667, 0.333, 0.667, 0.667, 0.667],
       [  nan,   nan, 0.   , 0.   , 0.   , 0.   , 0.   , 0.333, 0.333, 0.667, 0.667, 0.667],
       [  nan,   nan, 0.   , 0.   , 0.   , 0.   , 0.   , 0.333, 0.333, 0.667, 0.667, 0.667],
       [  nan,   nan, 0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.333, 0.667, 0.667],
       [  nan,   nan, 0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.333, 0.667, 0.667],
       [  nan,   nan, 0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.333, 0.667, 0.667],
       [  nan,   nan, 0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.333, 0.333],
       [  nan,   nan, 0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.333, 0.333],
       [  nan,   nan, 0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.   ],
       [  nan,   nan, 0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.   ]])
```

And the two-second window would return:

```
array([[1.   , 1.   , 1.   , 1.   , 1.   , 1.   , 1.   , 1.   , 1.   , 1.   , 1.   , 1.   ],
       [1.   , 1.   , 1.   , 1.   , 1.   , 1.   , 1.   , 1.   , 1.   , 1.   , 1.   , 1.   ],
       [1.   , 1.   , 1.   , 1.   , 1.   , 1.   , 1.   , 1.   , 1.   , 1.   , 1.   , 1.   ],
       [0.   , 0.5  , 0.5  , 0.667, 0.75 , 1.   , 1.   , 1.   , 1.   , 1.   , 1.   , 0.667],
       [0.   , 0.5  , 0.5  , 0.667, 0.75 , 1.   , 1.   , 1.   , 1.   , 1.   , 1.   , 0.667],
       [0.   , 0.   , 0.   , 0.333, 0.5  , 1.   , 1.   , 1.   , 1.   , 1.   , 1.   , 0.667],
       [0.   , 0.   , 0.   , 0.333, 0.5  , 1.   , 1.   , 1.   , 0.75 , 1.   , 1.   , 0.667],
       [0.   , 0.   , 0.   , 0.333, 0.5  , 1.   , 1.   , 1.   , 0.75 , 1.   , 1.   , 0.667],
       [0.   , 0.   , 0.   , 0.333, 0.5  , 1.   , 1.   , 1.   , 0.75 , 1.   , 1.   , 0.667],
       [0.   , 0.   , 0.   , 0.   , 0.25 , 1.   , 0.5  , 0.667, 0.5  , 1.   , 1.   , 0.667],
       [0.   , 0.   , 0.   , 0.   , 0.25 , 1.   , 0.5  , 0.667, 0.5  , 1.   , 1.   , 0.667],
       [0.   , 0.   , 0.   , 0.   , 0.   , 1.   , 0.5  , 0.667, 0.5  , 1.   , 1.   , 0.667],
       [0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.333, 0.25 , 1.   , 1.   , 0.667],
       [0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.333, 0.25 , 1.   , 1.   , 0.667],
       [0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 1.   , 1.   , 0.667],
       [0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 1.   , 1.   , 0.667],
       [0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 1.   , 1.   , 0.667],
       [0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.5  , 0.333],
       [0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.5  , 0.333],
       [0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.   ],
       [0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.   , 0.   ]])
```

## Explanation and Caveats

In both operational modes the windows are *trailing* windows. If the samples are known to be uniformly sampled then it's probably faster to run the first version and ignore the timestamps. However, it should be noted when computing *with* timestamps, the windows are only computed once, so the speedup is probably going to be operationally irrelavent, especially for large signals and many thresholds.

Some notes:

- When using the trailing samples mode, the window is always composed of exactly three samples. That means the first few columns will be empty (not enough elements).
- When using the trailing time period mode, the window is always *inclusive*.
- When using the trailing time period mode, data is filled in for all times, even if there is only one sample.

## License

The MIT License (MIT)

Copyright (c) 2019 Carnegie Mellon University Auton Lab

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
