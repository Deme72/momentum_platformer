import sys
import struct

def exist_check(fname):
    # Make sure we don't already have the destination file -- if we do
    # make *them* delete it
    try:
        open(fname, "r")
        return True
    except:
        return False
    

def break_ext(fname):
    dindex = fname.rfind(".")
    if dindex > 0:
        return (fname[:dindex], fname[dindex+1:].lower())
    else:
        return (fname, "")

def chr_to_s(src, dest):
    if exist_check(dest):
        return

    raw_data = None
    fp_out = open(dest, "w")
    
    fp_out.write("\n;;{w:8,h:8,bpp:1,count:256,brev:1,np:2,pofs:8,remap:[0,1,2,4,5,6,7,8,9,10,11,12]};;\n")
    fp_out.write(".segment \"CHARS\"\n")
    buff = ".byte "
    with open(src, mode="rb") as file:
        raw_data = file.read()


        data_len = len(raw_data)        # Should be 16384 (8x8x16x16)
        print(len(raw_data))
        count = 0
        num = 0
        for c in struct.iter_unpack("B", raw_data):
            #hstr = hex(int(c[0]))[2:]
            #print(c[0], type(c[0]))
            hstr = hex(c[0])[2:]
            if len(hstr) == 1:
                hstr = "0" + hstr
            buff += "$" + hstr
            count += 1
            num += 1
            if count < 8:
                buff += ","
            else:
                fp_out.write(buff + "\n")
                buff = ".byte "
                count = 0
                if num == 4096:
                    # Start the second CHR bank
                    fp_out.write(";;{w:8,h:8,bpp:1,count:256,brev:1,np:2,pofs:8,remap:[5,0,1,2,4,6,7,8,9,10,11,12]};;\n")
    fp_out.write(";;\n\n");
    fp_out.close()


def s_to_chr(src, dest):
    if exist_check(dest):
        return

    raw_data = None
    fp_out = open(dest, "wb")
    with open(src, mode="r") as file:
        file.readline()
        file.readline()
        file.readline()
        for line in file:
            line = line.strip()
            if len(line) > 6 and line[0:5] == ".byte":
                line = line[6:]
                elem = line.split(",")
                for i in range(len(elem)):
                    elem[i] = int(elem[i][1:], 16)
                print(elem)
                fp_out.write(bytes(elem))
    fp_out.close()

    

if __name__ == "__main__":
    num_args = len(sys.argv)
    dest = ""
    src = ""
    if num_args < 2:
        print("usage1: chr_to_s.py input.chr [output.s]")
        print("usage2: chr_to_s.py input.s [output.chr]")
    else:
        # Determine what we're trying to do from the command-line arguments
        src = sys.argv[1]
        mode = "?"
        if num_args == 3:
            dest = sys.argv[2]
            sname, sext = break_ext(src)
            dname, dext = break_ext(dest)
            if sext == "s" and dext == "chr":
                mode = "s2c"
            elif sext == "chr" and dext == "s":
                mode = "c2s"
        else:
            sname, sext = break_ext(src)
            if sext == "s":
                mode = "s2c"
                dest = sname + ".chr"
            elif sext == "chr":
                mode = "c2s"
                dest = sname + ".s"

        # Do the thing
        if mode == "s2c":
            s_to_chr(src, dest)
        elif mode == "c2s":
            chr_to_s(src, dest)
        else:
            print("Sorry, I can't tell what you're trying to do based on those command-line arguments")


        
