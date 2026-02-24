# Unseen-Codebases-Domain Data Synthesis and Training Based on Code Graphs


## Introduction

**UCD-Training** (Unseen-Codebase-Domain Training) is a two-stage training framework designed to inject codebase-specific knowledge into large language models using only source code implementations from unseen codebases. By constructing a code graph and performing reasoning-aware data synthesis, UCD-Training significantly improves LLMs' code generation capabilities on unseen codebases.

### The Problem

In practice, developers frequently work with codebases that are absent from LLM pretraining corpora, such as:
- Newly released libraries and frameworks
- Domain-specific frameworks
- Customized enterprise systems
- Proprietary third-party components

In these scenarios, LLMs typically exhibit severe performance degradation (**37-57%**) and high hallucination rates. Existing inference-time augmentation techniques (e.g., RAG) are insufficient because correct code generation requires understanding usage patterns and conventions among different components—knowledge that must be learned through training rather than merely retrieved.

### Our Approach

UCD-Training proposes a two-stage training framework:

1. **Dependency-Preserving Continued Pre-Training (CPT)**
2. **Graph-Grounded Supervised Fine-Tuning (SFT)**

## Method Overview


### Stage 1: Code Graph Construction

Perform program analysis on the source code of unseen codebases to extract:
- **Nodes**: Files, classes, functions, methods, global variables
- **Edges**: Dependency relations, call relations, include relations, locate relations

### Stage 2: Dependency-Preserving CPT

Extract file-level dependencies from the code graph and ensure files with dependency relationships appear in the same training sample through depth-first traversal:

1. Start depth-first traversal from nodes with zero in-degree
2. Use sliding-window strategy to construct training samples
3. Mix with general-domain data for CPT training

### Stage 3: Graph-Grounded SFT

Synthesize three types of data, each augmented with explicit reasoning traces:

| Data Type | Description | Purpose |
|-----------|-------------|---------|
| **Single-hop Relation Reasoning Data** | Constructed from edges and endpoint nodes in the code graph | Capture fine-grained structural relations among code entities |
| **Compositional API Reasoning Data** | Multiple types of code examination questions from API combinations extracted from internal test cases | Improve understanding of API combinations and functional scenarios |
| **Codebase Utilization Data** | Transform internal test cases into function generation tasks | Enhance ability to correctly use codebase APIs |

Each data type undergoes:
1. Data synthesis
2. Reasoning traces generation with ground-truth-level context
3. Post-filtering to eliminate low-quality samples

## Benchmark: UnseenCodeBench

We construct a code generation benchmark **UnseenCodeBench** targeting unseen codebases:

| Language | Project | Created Time | Stars | LOC | Files | Test Cases |
|----------|---------|--------------|-------|-----|-------|------------|
| C++ | sqlgen | 2025.3 | 131 | 14,164 | 213 | 60 |
| C++ | reaction | 2025.3 | 618 | 5,720 | 26 | 64 |
| C++ | Hexi | 2025.3 | 279 | 6,108 | 29 | 64 |
| Python | LEANN | 2025.6 | 8,038 | 7,491 | 14 | 64 |

## Project Structure

```
Unseen-Codebases-Domain-Data-Synthesis-and-Training-Based-on-Code-Graphs/
├── TrainingData/                          # Generated training data
│   ├── {project}/                          # Project-specific training data (hexi, leann, reaction, sqlgen)
│   │   ├── DependencyPreservingCPT/        # CPT training data
│   │   │   ├── source_code_{project}.json  # Source code data
│   │   │   └── general_data_{project}_CPT.json  # Mixed general-domain data
│   │   └── GraphGroundedSFT/               # SFT training data
│   │       ├── single_hop_relation_reasoning_data.json
│   │       ├── compositional_API_reasoning_data.json
│   │       ├── codebases_utilization_data.json
│   │       └── general_data_{project}_SFT.json
├── Evaluation/                            # Evaluation code
│   ├── run.sh                             # Evaluation script
│   ├── evaluation/                        # Core evaluation code
│   ├── test_scripts/                      # Test scripts
│   └── third_party_project/               # Target codebases
│       ├── Hexi/
│       ├── LEANN/
│       ├── reaction/
│       └── sqlgen/
└── Result/                                # Experimental results
    ├── RQ1/                               # RQ1: Performance comparison
    ├── RQ2/                               # RQ2: Ablation study
    ├── RQ3/                               # RQ3: Generality analysis
    ├── RQ4/                               # RQ4: Enterprise scenario simulation
    └── RQ5/                               # RQ5: Hyperparameter configuration
```

## Quick Start

### Requirements

- Python >= 3.11
- Clang (for C++ code parsing)
- Tree-sitter (for syntax analysis)

### Installation

```bash
git clone https://github.com/your-repo/UCD-Training.git
cd UCD-Training
pip install -r requirements.txt
```

### Evaluation

```bash
# Run evaluation
bash Evaluation/run.sh <model_name> <project> <eval_mode>

# Examples
bash Evaluation/run.sh Qwen3-14B hexi base
bash Evaluation/run.sh Qwen3-14B,Qwen3-8B hexi,leann rag
```
