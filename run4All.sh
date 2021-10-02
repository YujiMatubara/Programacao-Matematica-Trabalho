FILES="./*"
for f in $FILES
do
  echo "Tempo para $f:"
  time $1 $f
done
