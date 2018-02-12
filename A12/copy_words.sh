#!/bin/bash

users=$(cat users)

for user in $users
do
	scp wordlist $user:~/
	scp stopwords $user:~/
done

