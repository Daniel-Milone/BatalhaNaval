Naval Battle Challenge - Three Levels of Complexity
Welcome to the "Naval Battle" challenge! This project will challenge your programming skills using vectors and matrices to simulate a Naval Battle game, divided into three levels: Novice, Adventurer, and Master. In each level, new features will be added, making the challenge progressively more complex.

🏅 Novice Level
In this initial level, you will implement the basic logic of positioning ships on a Naval Battle board using two-dimensional vectors.

🚩 Objectives:
Ship Positioning: The system must simulate the location of two ships on the board, one positioned vertically and the other horizontally.
Use of Vectors: The ships will be positioned using two-dimensional vectors, with X and Y coordinates.
Coordinate Display: The system must display the coordinates of each part of the ships in the console using printf.

📥 Data Input:
Values ​​will be entered manually using variables in the code.

📤 Data Output:
After positioning, the system should display the ships' coordinates clearly and in an organized manner.

🏅 Adventurer Level
At the Adventurer level, you will expand the board and add more ships, including diagonal positions.

🆕 Difference from the Novice Level:
10x10 Board: The board will be expanded to a 10x10 matrix.
Placement of Four Ships: The system should position four ships, including two diagonally.
Full Board Display: The system will display the entire matrix, where 0 indicates a position without a ship and 3 indicates an occupied position.

🚩 New Features:
10x10 Matrix: Implementation of a larger matrix to represent the board.
Diagonal Ship Positioning: Addition of ships positioned diagonally.

Full Board Display: The system will show the complete board, indicating occupied and free positions.
🏅 Master Level
At the Master level, the challenge intensifies with the implementation of special abilities represented by specific matrices on the board.

🆕 Difference from the Adventurer Level:
Special Abilities: The system must define ability areas using matrices with specific patterns: cone, cross, and octahedron.
Nested Repetition Structures: Use of nested loops to traverse and fill the areas affected by the abilities.

🚩 New Features:
Ability Matrices: Implementation of three matrices to represent special abilities on the board.
Ability Patterns: Creation of specific patterns (cone, cross, octahedron) to define the affected areas.
Display of Affected Areas: The system will display the board with the affected areas, using 0 for unaffected areas and 1 for affected areas.

Example Output:
Example and command: printf("%d ",matrix[i][j]);

Example output of a cone skill:
0 0 1 0 0

0 1 1 1 0

1 1 1 1 1

Example output of an octahedron skill:
0 0 1 0 0

0 1 1 1 0

0 0 1 0 0

Example output of a cross skill:
0 0 1 0 0

1 1 1 1 1

0 0 1 0 0

📋 Common Functional Requirements
Data Input: Values ​​will be entered manually using variables in the code.
Use of Matrices: Data must be structured efficiently using matrices.
Display of Results: Results must be displayed clearly and in an organized manner.

📌 Common Non-Functional Requirements
Performance: The system must execute operations efficiently, without noticeable delays.
Documentation: The code must be well-documented, with clear comments on the function of each part of the code.
Maintainability: The code must be organized and easy to understand, facilitating future maintenance and expansions.

Good luck developing this challenge! Take the opportunity to improve your skills in vectors and matrices as you progress through the levels.

Teaching Team - MateCheck
