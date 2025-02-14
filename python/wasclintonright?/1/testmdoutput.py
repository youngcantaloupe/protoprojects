# Define file path and markers
file_path = "example.md"
start_marker = "# StartMarker"
end_marker = "# EndMarker"

# New content to insert between the markers
new_content = [
    "This is the new content replacing the old range.\n",
    "It can also have multiple lines.\n",
]

# Step 1: Read the file and locate markers
with open(file_path, "r") as file:
    lines = file.readlines()

# Find marker indices
start_index = None
end_index = None

for i, line in enumerate(lines):
    if start_marker in line:
        start_index = i
    elif end_marker in line:
        end_index = i

# Ensure both markers were found
if start_index is not None and end_index is not None and start_index < end_index:
    # Step 2: Replace content between markers (excluding markers themselves)
    lines[start_index + 1 : end_index] = new_content

    # Step 3: Write updated content back to the file
    with open(file_path, "w") as file:
        file.writelines(lines)
else:
    print("Markers not found or incorrectly placed in the file.")
