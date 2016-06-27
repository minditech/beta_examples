# DIMACS example C++ solver

This is an example solver for max-SAT problems with <a href="http://people.sc.fsu.edu/~jburkardt/data/cnf/cnf.html">DIMACS format</a>.

If you do not have one already, create a <a href="http://dockerhub.com">DockerHub</a> account.

Next do the follow steps:

## Clone the repository

    git clone git@github.com:minditech/dimacs_example.git

## Build the solver

    docker build -t DOCKERHUB_USERNAME/SOLVER_NAME:SOLVER_VERSION .

## Push to DockerHub

    docker login -u DOCKERHUB_USERNAME -p DOCKERHUB_PASSWORD
    docker push DOCKERHUB_USERNAME/SOLVER_NAME:SOLVER_VERSION
