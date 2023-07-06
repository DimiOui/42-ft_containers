# ft_containers
The ft_containers project provides a re-implementation of popular C++ standard library containers such as **`vector`**, **`map`**, and **`stack`**. By implementing these containers from scratch, I gained insights into the underlying data structures, algorithms, and design considerations involved in creating efficient and well-tested container classes.
This project served as an exercise to develop a solid understanding of container operations, memory management, iterators, and custom allocators.
<br/>

## Containers Implemented
The following containers have been implemented as part of this project:

- **`vector`**: A dynamic array that provides dynamic size, efficient random access, and automatic memory management. The implementation includes functionalities such as inserting elements, accessing elements, resizing the container, and iterating over the elements.
<br/>

- **`map`**: An associative container that stores key-value pairs in a sorted manner, providing fast lookup, insertion, and deletion based on the key. The implementation includes functionalities such as inserting elements, finding elements, erasing elements, and iterating over the elements.
<br/>

- **`stack`**: A container adapter that provides a Last-In-First-Out (LIFO) stack interface, built on top of another container. The implementation includes functionalities such as pushing elements onto the stack, popping elements from the stack, and accessing the top element.
Each container is implemented as a template class, allowing flexibility in the type of elements stored. Additionally, custom iterators and reverse iterators are implemented to provide traversal and manipulation capabilities for the containers.

## Project Structure
The project is organized as follows:

- `containers/`: Contains the header files for each container, as well as any required utility files.
- `iterators/`: Contains the iterator classes used by the containers.
- `utils/`: Contains utility files, such as comparison functions or other helper classes.
- `srcs/`: Contains the `main.cpp` for testing purposes.

## Usage
To use the ft_containers in your own project, follow these steps:

1. Clone the repository: ```git clone https://github.com/DimiOui/42-ft_containers.git```
2. Include the desired container header file(s) in your source code (or test it with the `main.cpp` file).
3. Compile your code along with the container source files.
Here's an example of how to use the vector container:

```
#include "includes/vector.hpp"

int main() {
    ft::vector<int> numbers;
    numbers.push_back(1);
    numbers.push_back(2);
    numbers.push_back(3);

    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
```
The repository includes a `main.cpp` file with basic tests for each container. 
The test file covers various aspects of the container functionality, such as inserting elements, accessing elements, iterating over the containers, and performing basic operations. These tests ensure that the containers are implemented correctly and behave as expected.

## Concepts Learned
The ft_containers project encompasses various concepts and topics related to container classes and C++ programming.
One of the key concepts learned from the implementation of the map container is **red-black trees**.
<br/>

A **red-black tree** is a self-balancing binary search tree that ensures efficient operations such as insertion, deletion, and searching. The tree maintains a set of properties that ensure it remains balanced, preventing it from degenerating into a linear data structure.
<br/>

The main properties of a red-black tree are:

1. **Binary Search Tree Property**: The left child of a node has a key less than the node's key, and the right child has a key greater than or equal to the node's key.

2. **Red-Black Property**: Each node is either red or black. The root and leaves (null nodes) are always black. No two adjacent nodes can be red, and every path from the root to a leaf contains the same number of black nodes.
<br/>
<br/>

By maintaining these properties, red-black trees provide guaranteed logarithmic time complexity for operations such as insertion, deletion, and searching.
<br/>

In the `map` container implementation, a red-black tree is used as the underlying data structure to store key-value pairs in a sorted manner. The red-black tree ensures efficient lookups and insertions while maintaining the sorted order of elements.
Overall, the implementation of the `map` container with a red-black tree provides valuable insights into data structures, algorithmic design, and the importance of balancing techniques for efficient container implementations.
<br/>

Other key concepts learned from this project include:
- Container design and implementation
- Dynamic memory allocation and deallocation
- Data structures such as arrays, binary trees, and linked lists
- Iterator design and implementation
- Template metaprogramming
- Custom allocators
- Comparators and comparison functions
- Operator overloading
- Copy construction and assignment
- Exception handling
- Code organization and modularity
