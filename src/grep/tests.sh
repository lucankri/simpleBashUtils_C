#!/bin/bash
SETCOLOR_SUCCESS="echo \\033[1;32m"
SETCOLOR_FAILURE="echo \\033[1;31m"
SETCOLOR_NORMAL="echo \\033[0;39m"

NUM_SUCCESS=0
NUM_FAIL=0
NUM_TOTAL=0

file="lorem"
pattern_e="L e 11 doesnt_est"
pattern="est doesnt_exist"
regular="'[A-Za-z0-9]' '[A-Za-z0-9_]' '[0-9]' '[^0-9]' '[a-z]' '[^\t\r\n\v\f]'"

# without flag - 1 file 
for pattern_1 in $pattern_e $regular
do
  ./s21_grep $pattern_1 $file > s21_grep.txt
  grep $pattern_1 $file > grep.txt
  res="$(diff -s s21_grep.txt grep.txt)"
  if [ "$res" == "Files s21_grep.txt and grep.txt are identical" ]
    then
      ${SETCOLOR_SUCCESS}
      (( NUM_SUCCESS++ ))
      (( NUM_TOTAL++ ))
      echo "$NUM_TOTAL. $flag_e $pattern_1 $flag_e $pattern_2 $flag_e $pattern_3 $file"
      ${SETCOLOR_NORMAL}
    else
    #   echo "$TEST1" >> log.txt
      ${SETCOLOR_FAILURE}
      (( NUM_FAIL++ ))
      (( NUM_TOTAL++ ))
      echo "$NUM_TOTAL. | failed | $flag_e $pattern_1 $flag_e $pattern_2 $flag_e $pattern_3 $file"
      ${SETCOLOR_NORMAL}
        exit 1;
  fi
  rm s21_grep.txt grep.txt
done


# without flag - 2 files
file="l"
for pattern_1 in $pattern $regular
do
  ./s21_grep $pattern_1 $file > s21_grep.txt
  grep $pattern_1 $file > grep.txt
  res="$(diff -s s21_grep.txt grep.txt)"
  if [ "$res" == "Files s21_grep.txt and grep.txt are identical" ]
    then
      ${SETCOLOR_SUCCESS}
      (( NUM_SUCCESS++ ))
      (( NUM_TOTAL++ ))
      echo "$NUM_TOTAL. $flag_e $pattern_1 $flag_e $pattern_2 $flag_e $pattern_3 $file"
      ${SETCOLOR_NORMAL}
    else
    #   echo "$TEST1" >> log.txt
      ${SETCOLOR_FAILURE}
      (( NUM_FAIL++ ))
      (( NUM_TOTAL++ ))
      echo "$NUM_TOTAL. | failed | $flag_e $pattern_1 $flag_e $pattern_2 $flag_e $pattern_3 $file"
      ${SETCOLOR_NORMAL}
        exit 1;
  fi
  rm s21_grep.txt grep.txt
done


# e 
flag_e="-e"

for pattern_1 in $pattern_e $regular
do
  for pattern_2 in $pattern_e $regular
  do
    for pattern_3 in $pattern_e $regular
    do
      ./s21_grep $flag_e $pattern_1 $flag_e $pattern_2 $flag_e $pattern_3 $file > s21_grep.txt
      grep $flag_e $pattern_1 $flag_e $pattern_2 $flag_e $pattern_3 $file > grep.txt
      res="$(diff -s s21_grep.txt grep.txt)"
      if [ "$res" == "Files s21_grep.txt and grep.txt are identical" ]
        then
          ${SETCOLOR_SUCCESS}
          (( NUM_SUCCESS++ ))
          (( NUM_TOTAL++ ))
          echo "$NUM_TOTAL. $flag_e $pattern_1 $flag_e $pattern_2 $flag_e $pattern_3 $file"
          ${SETCOLOR_NORMAL}
        else
        #   echo "$TEST1" >> log.txt
          ${SETCOLOR_FAILURE}
          (( NUM_FAIL++ ))
          (( NUM_TOTAL++ ))
          echo "$NUM_TOTAL. | failed | $flag_e $pattern_1 $flag_e $pattern_2 $flag_e $pattern_3 $file"
          ${SETCOLOR_NORMAL}
           exit 1;
      fi
      rm s21_grep.txt grep.txt
    done
  done
done


# est - exists
# no_est - don't exist
# 4 - exists

# e n i v c l s
pattern_e="-fflagf"
for flag in e n i v c l s
do
  for pattern in $pattern_e
    do
      ./s21_grep -$flag $pattern $file > s21_grep.txt
      grep -$flag $pattern $file > grep.txt
      res="$(diff -s s21_grep.txt grep.txt)"
      if [ "$res" == "Files s21_grep.txt and grep.txt are identical" ]
        then
          ${SETCOLOR_SUCCESS}
          (( NUM_SUCCESS++ ))
          (( NUM_TOTAL++ ))
          echo "$NUM_TOTAL. -$flag $pattern $file"
          ${SETCOLOR_NORMAL}
        else
        #   echo "$TEST1" >> log.txt
          ${SETCOLOR_FAILURE}
          (( NUM_FAIL++ ))
          (( NUM_TOTAL++ ))
          echo "$NUM_TOTAL. | failed | -$flag $pattern $file"
          ${SETCOLOR_NORMAL}
           exit 1;
      fi
      rm s21_grep.txt grep.txt
  done
done


# 2 flag 1 file
for flag_1 in n i c s o
do
  for flag_2 in e n i c s o
  do
    for pattern in $patterns $regular
      do
        ./s21_grep -$flag_1 -$flag_2 $pattern $file > s21_grep.txt
        grep -$flag_1 -$flag_2 $pattern $file > grep.txt
        res="$(diff -s s21_grep.txt grep.txt)"
        if [ "$res" == "Files s21_grep.txt and grep.txt are identical" ]
          then
            ${SETCOLOR_SUCCESS}
            (( NUM_SUCCESS++ ))
            (( NUM_TOTAL++ ))
            echo "$NUM_TOTAL. -$flag_1 -$flag_2 $pattern $file"
            ${SETCOLOR_NORMAL}
          else
          #   echo "$TEST1" >> log.txt
            ${SETCOLOR_FAILURE}
            (( NUM_FAIL++ ))
            (( NUM_TOTAL++ ))
            echo "$NUM_TOTAL. | failed | -$flag_1 -$flag_2 $pattern $file"
            ${SETCOLOR_NORMAL}
            exit 1;
        fi
        rm s21_grep.txt grep.txt
    done
  done
done

# flags together
for flag_1 in n i v l s
do
  for flag_2 in e n i v l s
  do
    for pattern in $patterns $regular
      do
        ./s21_grep -$flag_1$flag_2 $pattern $file > s21_grep.txt
        grep -$flag_1$flag_2 $pattern $file > grep.txt
        res="$(diff -s s21_grep.txt grep.txt)"
        if [ "$res" == "Files s21_grep.txt and grep.txt are identical" ]
          then
            ${SETCOLOR_SUCCESS}
            (( NUM_SUCCESS++ ))
            (( NUM_TOTAL++ ))
            echo "$NUM_TOTAL. -$flag_1$flag_2 $pattern $file "
            ${SETCOLOR_NORMAL}
          else
          #   echo "$TEST1" >> log.txt
            ${SETCOLOR_FAILURE}
            (( NUM_FAIL++ ))
            (( NUM_TOTAL++ ))
            echo "$NUM_TOTAL. | failed | -$flag_1$flag_2 $pattern $file "
            ${SETCOLOR_NORMAL}
            exit 1;
        fi
        rm s21_grep.txt grep.txt
    done
  done
done

# 3 flag 1 file
for flag_1 in n i c s o
do
  for flag_2 in n i c s o
  do
    for flag_3 in e n i c s o
    do
      for pattern in $patterns $regular
        do
          ./s21_grep -$flag_1 -$flag_2 -$flag_3 $pattern $file > s21_grep.txt
          grep -$flag_1 -$flag_2 -$flag_3 $pattern $file > grep.txt
          res="$(diff -s s21_grep.txt grep.txt)"
          if [ "$res" == "Files s21_grep.txt and grep.txt are identical" ]
            then
              ${SETCOLOR_SUCCESS}
              (( NUM_SUCCESS++ ))
              (( NUM_TOTAL++ ))
              echo "$NUM_TOTAL. -$flag_1 -$flag_2 -$flag_3 $pattern $file"
              ${SETCOLOR_NORMAL}
            else
            #   echo "$TEST1" >> log.txt
              ${SETCOLOR_FAILURE}
              (( NUM_FAIL++ ))
              (( NUM_TOTAL++ ))
              echo "$NUM_TOTAL. | failed | -$flag_1 -$flag_2 -$flag_3 $pattern $file"
              ${SETCOLOR_NORMAL}
              exit 1;
          fi
          rm s21_grep.txt grep.txt
      done
    done
  done
done


# # 3 flag 1 file
# for flag_1 in n i v c l s
# do
#   for flag_2 in n i v c l s
#   do
#     for flag_3 in n i v c l s
#     do
#       for flag_4 in e n i v c l s
#       do    
#         for pattern in est
#           do
#             ./s21_grep -$flag_1 -$flag_2 -$flag_3 -$flag_4 $pattern $file > s21_grep.txt
#             grep -$flag_1 -$flag_2 -$flag_3 -$flag_4 $pattern $file > grep.txt
#             res="$(diff -s s21_grep.txt grep.txt)"
#             if [ "$res" == "Files s21_grep.txt and grep.txt are identical" ]
#               then
#                 ${SETCOLOR_SUCCESS}
#                 (( NUM_SUCCESS++ ))
#                 (( NUM_TOTAL++ ))
#                 echo "$NUM_TOTAL. -$flag_1 -$flag_2 -$flag_3 -$flag_4 $pattern $file"
#                 ${SETCOLOR_NORMAL}
#               else
#               #   echo "$TEST1" >> log.txt
#                 ${SETCOLOR_FAILURE}
#                 (( NUM_FAIL++ ))
#                 (( NUM_TOTAL++ ))
#                 echo "$NUM_TOTAL. | failed | -$flag_1 -$flag_2 -$flag_3 -$flag_4 $pattern $file"
#                 ${SETCOLOR_NORMAL}
#                 exit 1;
#             fi
#             rm s21_grep.txt grep.txt
#         done
#       done
#     done
#   done
# done


# # 3 flag 1 file
# for flag_1 in n i v c l s
# do
#   for flag_2 in n i v c l s
#   do
#     for flag_3 in n i v c l s
#     do
#       for flag_4 in n i v c l s
#       do
#         for flag_5 in e n i v c l s
#         do
#           for pattern in est
#             do
#               ./s21_grep -$flag_1 -$flag_2 -$flag_3 -$flag_4 -$flag_5 $pattern $file > s21_grep.txt
#               grep -$flag_1 -$flag_2 -$flag_3 -$flag_4 -$flag_5 $pattern $file > grep.txt
#               res="$(diff -s s21_grep.txt grep.txt)"
#               if [ "$res" == "Files s21_grep.txt and grep.txt are identical" ]
#                 then
#                   ${SETCOLOR_SUCCESS}
#                   (( NUM_SUCCESS++ ))
#                   (( NUM_TOTAL++ ))
#                   echo "$NUM_TOTAL. -$flag_1 -$flag_2 -$flag_3 -$flag_4 -$flag_5 $pattern $file"
#                   ${SETCOLOR_NORMAL}
#                 else
#                 #   echo "$TEST1" >> log.txt
#                   ${SETCOLOR_FAILURE}
#                   (( NUM_FAIL++ ))
#                   (( NUM_TOTAL++ ))
#                   echo "$NUM_TOTAL. | failed | -$flag_1 -$flag_2 -$flag_3 -$flag_4 -$flag_5 $pattern $file"
#                   ${SETCOLOR_NORMAL}
#                   exit 1;
#               fi
#               rm s21_grep.txt grep.txt
#           done
#         done
#       done
#     done
#   done
# done


# # 3 flag 1 file
# for flag_1 in n i v c l s
# do
#   for flag_2 in n i v c l s
#   do
#     for flag_3 in n i v c l s
#     do
#       for flag_4 in n i v c l s
#       do
#         for flag_5 in n i v c l s
#         do
#           for flag_6 in e n i v c l s
#           do        
#             for pattern in est
#               do
#                 ./s21_grep -$flag_1 -$flag_2 -$flag_3 -$flag_4 -$flag_5 -$flag_6 $pattern $file > s21_grep.txt
#                 grep -$flag_1 -$flag_2 -$flag_3 -$flag_4 -$flag_5 -$flag_6 $pattern $file > grep.txt
#                 res="$(diff -s s21_grep.txt grep.txt)"
#                 if [ "$res" == "Files s21_grep.txt and grep.txt are identical" ]
#                   then
#                     ${SETCOLOR_SUCCESS}
#                     (( NUM_SUCCESS++ ))
#                     (( NUM_TOTAL++ ))
#                     echo "$NUM_TOTAL. -$flag_1 -$flag_2 -$flag_3 -$flag_4 -$flag_5 -$flag_6 $pattern $file"
#                     ${SETCOLOR_NORMAL}
#                   else
#                   #   echo "$TEST1" >> log.txt
#                     ${SETCOLOR_FAILURE}
#                     (( NUM_FAIL++ ))
#                     (( NUM_TOTAL++ ))
#                     echo "$NUM_TOTAL. | failed | -$flag_1 -$flag_2 -$flag_3 -$flag_4 -$flag_5 -$flag_6 $pattern $file"
#                     ${SETCOLOR_NORMAL}
#                     exit 1;
#                 fi
#                 rm s21_grep.txt grep.txt
#             done
#           done
#         done
#       done
#     done
#   done
# done

# 2 files
file="lorem l"

# e 
flag_e="-e"

for pattern_1 in $pattern_e $regular
do
  for pattern_2 in $pattern_e $regular
  do
    for pattern_3 in $pattern_e $regular
    do
      ./s21_grep $flag_e $pattern_1 $flag_e $pattern_2 $flag_e $pattern_3 $file > s21_grep.txt
      grep $flag_e $pattern_1 $flag_e $pattern_2 $flag_e $pattern_3 $file > grep.txt
      res="$(diff -s s21_grep.txt grep.txt)"
      if [ "$res" == "Files s21_grep.txt and grep.txt are identical" ]
        then
          ${SETCOLOR_SUCCESS}
          (( NUM_SUCCESS++ ))
          (( NUM_TOTAL++ ))
          echo "$NUM_TOTAL. $flag_e $pattern_1 $flag_e $pattern_2 $flag_e $pattern_3 $file"
          ${SETCOLOR_NORMAL}
        else
        #   echo "$TEST1" >> log.txt
          ${SETCOLOR_FAILURE}
          (( NUM_FAIL++ ))
          (( NUM_TOTAL++ ))
          echo "$NUM_TOTAL. | failed | $flag_e $pattern_1 $flag_e $pattern_2 $flag_e $pattern_3 $file"
          ${SETCOLOR_NORMAL}
          exit 1;
      fi
      rm s21_grep.txt grep.txt
    done
  done
done


# est - exists
# no_est - don't exist
# 4 - exists
for flag in e n i v c h s
do
  for pattern in $patterns $regular
    do
      ./s21_grep -$flag $pattern $file > s21_grep.txt
      grep -$flag $pattern $file > grep.txt
      res="$(diff -s s21_grep.txt grep.txt)"
      if [ "$res" == "Files s21_grep.txt and grep.txt are identical" ]
        then
          ${SETCOLOR_SUCCESS}
          (( NUM_SUCCESS++ ))
          (( NUM_TOTAL++ ))
          echo "$NUM_TOTAL. -$flag $pattern $file"
          ${SETCOLOR_NORMAL}
        else
        #   echo "$TEST1" >> log.txt
          ${SETCOLOR_FAILURE}
          (( NUM_FAIL++ ))
          (( NUM_TOTAL++ ))
          echo "$NUM_TOTAL. | failed | -$flag $pattern $file"
          ${SETCOLOR_NORMAL}
          exit 1;
      fi
      rm s21_grep.txt grep.txt
  done
done

for flag_1 in n i l s o
do
  for flag_2 in e n i l s o
  do
    for pattern in $patterns $regular
      do
        ./s21_grep -$flag_1 -$flag_2 $pattern $file > s21_grep.txt
        grep -$flag_1 -$flag_2 $pattern $file > grep.txt
        res="$(diff -s s21_grep.txt grep.txt)"
        if [ "$res" == "Files s21_grep.txt and grep.txt are identical" ]
          then
            ${SETCOLOR_SUCCESS}
            (( NUM_SUCCESS++ ))
            (( NUM_TOTAL++ ))
            echo "$NUM_TOTAL. -$flag_1 -$flag_2 $pattern $file"
            ${SETCOLOR_NORMAL}
          else
          #   echo "$TEST1" >> log.txt
            ${SETCOLOR_FAILURE}
            (( NUM_FAIL++ ))
            (( NUM_TOTAL++ ))
            echo "$NUM_TOTAL. | failed | -$flag_1 -$flag_2 $pattern $file"
            ${SETCOLOR_NORMAL}
            exit 1;
        fi
        rm s21_grep.txt grep.txt
    done
  done
done

# flags together
for flag_1 in n i v c s
do
  for flag_2 in e n i v c s
  do
    for pattern in $patterns $regular
      do
        ./s21_grep -$flag_1$flag_2 $pattern $file > s21_grep.txt
        grep -$flag_1$flag_2 $pattern $file > grep.txt
        res="$(diff -s s21_grep.txt grep.txt)"
        if [ "$res" == "Files s21_grep.txt and grep.txt are identical" ]
          then
            ${SETCOLOR_SUCCESS}
            (( NUM_SUCCESS++ ))
            (( NUM_TOTAL++ ))
            echo "$NUM_TOTAL. -$flag_1$flag_2 $pattern $file "
            ${SETCOLOR_NORMAL}
          else
          #   echo "$TEST1" >> log.txt
            ${SETCOLOR_FAILURE}
            (( NUM_FAIL++ ))
            (( NUM_TOTAL++ ))
            echo "$NUM_TOTAL. | failed | -$flag_1$flag_2 $pattern $file "
            ${SETCOLOR_NORMAL}
            exit 1;
        fi
        rm s21_grep.txt grep.txt
    done
  done
done

# s Подавляет сообщения об ошибках о несуществующих или нечитаемых файлах.

file="lorem l doesnt_exist"
flag="s"

for pattern in $patterns $regular
  do
    ./s21_grep -$flag $pattern $file > s21_grep.txt
    grep -$flag $pattern $file > grep.txt
    res="$(diff -s s21_grep.txt grep.txt)"
    if [ "$res" == "Files s21_grep.txt and grep.txt are identical" ]
      then
        ${SETCOLOR_SUCCESS}
        (( NUM_SUCCESS++ ))
        (( NUM_TOTAL++ ))
        echo "$NUM_TOTAL. -$flag $pattern $file"
        ${SETCOLOR_NORMAL}
      else
      #   echo "$TEST1" >> log.txt
        ${SETCOLOR_FAILURE}
        (( NUM_FAIL++ ))
        (( NUM_TOTAL++ ))
        echo "$NUM_TOTAL. | failed | -$flag $pattern $file"
        ${SETCOLOR_NORMAL}
        exit 1;
    fi
    rm s21_grep.txt grep.txt
done



# file="doesnt_exist"
# ./s21_grep -$flag  $file > s21_grep.txt
# grep -$flag $pattern $file > grep.txt
# res="$(diff -s s21_grep.txt grep.txt)"
# if [ "$res" == "Files s21_grep.txt and grep.txt are identical" ]
#   then
#     ${SETCOLOR_SUCCESS}
#     (( NUM_SUCCESS++ ))
#     (( NUM_TOTAL++ ))
#     echo "$NUM_TOTAL. -$flag $pattern $file"
#     ${SETCOLOR_NORMAL}
#   else
#   #   echo "$TEST1" >> log.txt
#     ${SETCOLOR_FAILURE}
#     (( NUM_FAIL++ ))
#     (( NUM_TOTAL++ ))
#     echo "$NUM_TOTAL. | failed | -$flag $pattern $file"
#     ${SETCOLOR_NORMAL}
#     exit 1;
# fi
# rm s21_grep.txt grep.txt



echo "-------------------------------------------
Total $NUM_TOTAL
Success: $NUM_SUCCESS | Fail: $NUM_FAIL"
