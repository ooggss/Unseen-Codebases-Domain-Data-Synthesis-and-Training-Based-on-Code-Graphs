#!/bin/bash

# Usage
usage() {
    echo "Usage: $0 <target_model_name> <target_project> <eval_mode>"
    echo ""
    echo "Parameters:"
    echo "  target_model_name  Model name(s), multiple models separated by comma (e.g., model1,model2,model3)"
    echo "  target_project     Project name(s), multiple projects separated by comma (e.g., hexi,leann,reaction,sqlgen)"
    echo "  eval_mode          Evaluation mode: rag or base"
    echo "                     - rag:  Use {project}_test_cases_baseline_RAG.json"
    echo "                     - base: Use test_cases.json"
    echo ""
    echo "Available projects: hexi, leann, reaction, sqlgen"
    echo ""
    echo "Examples:"
    echo "  $0 Qwen3-14B hexi base"
    echo "  $0 Qwen3-14B,Qwen3-8B hexi,leann rag"
    exit 1
}

# Check number of arguments
if [ $# -ne 3 ]; then
    echo "Error: 3 arguments required"
    usage
fi

target_model_name="$1"
target_project="$2"
eval_mode="$3"

# Validate eval_mode parameter
if [ "$eval_mode" != "rag" ] && [ "$eval_mode" != "base" ]; then
    echo "Error: eval_mode must be 'rag' or 'base'"
    usage
fi

# Get script directory
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Available project list
VALID_PROJECTS="hexi leann reaction sqlgen"

# Validate project name
validate_project() {
    local project="$1"
    for valid in $VALID_PROJECTS; do
        if [ "$project" == "$valid" ]; then
            return 0
        fi
    done
    return 1
}

# Convert comma-separated project string to array
IFS=',' read -ra PROJECT_ARRAY <<< "$target_project"

# Validate all projects
for project in "${PROJECT_ARRAY[@]}"; do
    project=$(echo "$project" | xargs)  # Trim whitespace
    if ! validate_project "$project"; then
        echo "Error: Invalid project name '$project'"
        echo "Available projects: $VALID_PROJECTS"
        exit 1
    fi
done

echo "=========================================="
echo "Starting evaluation tasks"
echo "Model(s): $target_model_name"
echo "Project(s): $target_project"
echo "Mode: $eval_mode"
echo "=========================================="

# Execute projects sequentially
for project in "${PROJECT_ARRAY[@]}"; do
    project=$(echo "$project" | xargs)  # Trim whitespace
    
    echo ""
    echo "------------------------------------------"
    echo "Processing project: $project"
    echo "------------------------------------------"
    
    # Enter the project's test_scripts directory
    PROJECT_DIR="$SCRIPT_DIR/test_scripts/$project/test_scripts"
    
    if [ ! -d "$PROJECT_DIR" ]; then
        echo "Error: Project directory does not exist: $PROJECT_DIR"
        exit 1
    fi
    
    cd "$PROJECT_DIR" || exit 1
    
    # Select test cases file based on eval_mode
    if [ "$eval_mode" == "rag" ]; then
        test_cases_file="${project}_test_cases_baseline_RAG.json"
    else
        test_cases_file="test_cases.json"
    fi
    
    echo "Working directory: $(pwd)"
    echo "Test cases file: $test_cases_file"
    echo "Executing: python3 run_test_private.py $target_model_name generate_result_$project test_result_$project/ ../evaluation/$project/$test_cases_file"
    
    # Execute test script
    python3 run_test_private.py "$target_model_name" "generate_result_$project" "test_result_$project/" "../evaluation/$project/$test_cases_file"
    
    exit_code=$?
    if [ $exit_code -ne 0 ]; then
        echo "Warning: Project $project returned non-zero exit code: $exit_code"
    else
        echo "Project $project completed successfully"
    fi
done

echo ""
echo "=========================================="
echo "All evaluation tasks completed"
echo "=========================================="
