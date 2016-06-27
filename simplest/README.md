# Login to dockerhub.com
docker login -u your_dockerhub_username -p your_dockerhub_password

# Build container
docker build -t your_dockerhub_username/your_solver_name:your_solver_version .

# Push container to repository
docker push your_dockerhub_username/your_solver_name
