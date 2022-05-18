import gen_enum
import gen_struct

# import gen_alloc
import gen_trie
import gen_line_alloc

if __name__ == "__main__":
    gen_enum.main()
    gen_struct.main()
    # gen_alloc.main()
    gen_trie.main()
    gen_line_alloc.main()
