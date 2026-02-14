

// The original test is just a placeholder asserting true.
// We encapsulate that behavior in a trivial function.

struct ResourceClassWithSBOResult {
    bool placeholder;
};

ResourceClassWithSBOResult run_resource_class_with_sbo() {
    return ResourceClassWithSBOResult{true};
}

