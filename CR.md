This file includes general CR comments.
For more specific comments, look for comments containing CR in the source files.
Also, in some cases comments may hold for several parts of the code, but to
avoid repeating myself, I only specified each comment once.

- I've seen that you formatted your code. Nice! Now, what if I wanted to add
	code to your library? How should I format it? You can't rely on my local
	configuration. The correct thing to do is to include a `.clang-format` file in
	your project. Look into [https://clang.llvm.org/docs/ClangFormat.html] for
	easy instruction about how to create such a file.
- Usually you don't include executable files in your git tree. This reduces
	bloat in your project. Create a `.gitignore` file to automatically exclude
	files (or directories) from your git tree.
