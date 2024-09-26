# Stage 1: Build stage
FROM gcc:latest AS builder

# Install required packages
RUN apt-get update && apt-get install -y \
    cmake \
    make \
    git \
    libgtest-dev \
    && rm -rf /var/lib/apt/lists/*

# Set the working directory
WORKDIR /app

# Copy project files
COPY . .

# Create a build directory and compile the project
RUN mkdir build && cd build && \
    cmake -DCMAKE_BUILD_TYPE=Release .. && \
    make

# Stage 2: Test stage
FROM builder AS tester

WORKDIR /app/build

# Run tests
CMD ["ctest", "--output-on-failure"]

# Stage 3: Run stage
FROM ubuntu:latest AS runner

# Install runtime dependencies
RUN apt-get update && apt-get install -y \
    libstdc++6 \
    && rm -rf /var/lib/apt/lists/*

# Set the working directory
WORKDIR /app

# Copy the built application from the builder stage
COPY --from=builder /app/build/water-and-jug .

# Entry point to run the application
ENTRYPOINT ["./water-and-jug"]
