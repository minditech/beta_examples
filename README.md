# Login to dockerhub.com
docker login -u DOCKERHUB_USERNAME -p DOCKERHUB_PASSWORD

# Build container
docker build -t DOCKERHUB_USERNAME/SOLVER_NAME:SOLVER_VERSION .

# Push container to repository
docker push DOCKERHUB_USERNAME/SOLVER_NAME:SOLVER_VERSION
