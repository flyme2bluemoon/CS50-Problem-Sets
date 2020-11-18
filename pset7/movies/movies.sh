for i in {1..13}
do
   cat $i.sql | sqlite3 movies.db
done