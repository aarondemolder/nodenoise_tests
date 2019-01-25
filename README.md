# nodenoise_tests

nodenoise ended up being a larger amount of classes than I expected, and a few could even be merged into the same class for different types of data - but in keeping track of these I kept them seperate for ease of understanding.

My development was more based on visual results - checking if changing values acted accordingly on the resulting image

The tests reflect both these points, with tests that verify a specific 'new' feature for:

* Frequency Data (numbers from a spinbox)
* AutoGradient Data (option selection from a combobox, returning an index value)
* Bounds Data (a selection of numbers from spinboxes in the same node)
* Colour Data (QColor Values)
* HeightMap Data (Check and Set values for boundaries from within the heightmap builder)
* Terrain Data (Using Perlin as an example, setting and getting frequency)

Generally the tests are default constructors, getters, setters, checking node IDs and copy constructors.

I also wanted to add tests for the node registry, creation & connections but this didn't work out.
