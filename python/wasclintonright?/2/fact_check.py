import csv
import os
import re
from datetime import date
import matplotlib.pyplot as plt
from typing import List, Dict, Tuple


def parse_data(file_path: str, cutoff: date) -> List[Dict[str, int]]:
    """
    Parses job data and filters it by a cutoff date.

    Args:
        file_path (str): Path to the CSV file.
        cutoff (datetime): The latest date to include in the data.

    Returns:
        list: A list of dictionaries with 'date' and 'jobs' keys.
    """
    jobs = []
    totmonth = 0
    try:
        with open(file_path, "r") as file:
            reader = csv.reader(file)
            for index, row in enumerate(reader):
                if index <= 5:  # Skip metadata
                    continue

                year = int(row[0])
                for month_idx, value in enumerate(row[1:], start=1):
                    if not value.strip():  # Skip empty values
                        continue

                    month = date(year, month_idx, 1)
                    if month > cutoff:  # Skip rows beyond the cutoff
                        continue

                    jobs.append({"date": month, "jobs": int(value)})
                    totmonth += 1

        print(f"parsing_data: total months:{totmonth}, {file_path}")
    except FileNotFoundError:
        print(f"Error: File '{file_path}' not found.")
    except Exception as e:
        print(f"An error occurred while parsing '{file_path}': {e}")
    return jobs


def parse_presidents(file_path: str) -> List[Dict[str, date]]:
    """
    Parses presidents' term data from a CSV file.

    Args:
        file_path (str): Path to the CSV file.

    Returns:
        list: A list of dictionaries with 'term start', 'term end', 'name', and 'party'.
    """
    presidents = []
    try:
        with open(file_path, "r") as file:
            reader = csv.DictReader(file)
            for row in reader:
                try:
                    row["term start"] = date(*map(int, row["term start"].split("-")))
                    row["term end"] = date(*map(int, row["term end"].split("-")))
                except ValueError as e:
                    print(f"Error parsing date for row: {row}. Error: {e}")
                    continue

                presidents.append(row)
                # print(row)
                # print(row["term start"])
    except FileNotFoundError:
        print(f"Error: File '{file_path}' not found.")
    except Exception as e:
        print(f"An error occurred while parsing '{file_path}': {e}")
    return presidents


def find_president_for_date(
    job_date: date, presidents: List[Dict[str, date]]
) -> Tuple[str, str]:
    """
    Finds the president and party in office for a given date.

    Args:
        date (str): The date to check.
        presidents (List[Dict[str, str]): List of president term data.

    Returns:
        Tuple[str, str]: Tuple containing the president's name and party.
    """
    for president in presidents:
        if president["term start"] <= job_date <= president["term end"]:
            # print(president["name"], president["party"])
            return (str(president["name"]), str(president["party"]))
    return ("", "")


def merge_data(
    job_data: List[Dict[str, int]],
    presidents: List[Dict[str, str]],
) -> None:
    """
    Merges president data into job data by adding 'president' and 'party' keys to each job entry.

    Args:
        job_data (List[Dict[str, str]]): Job data with dates and job counts.
        presidents (List[Dict[str, str]]): President term data.
    """
    for entry in job_data:
        entry["president"], entry["party"] = find_president_for_date(
            entry["date"], presidents
        )


def calculate_contributions(
    job_data: List[Dict[str, int]]
) -> Dict[str, Dict[str, int]]:
    """
    Calculates net contributions, gains, and decreases for each party.

    Args:
        job_data (list): A list of dictionaries with job and party information.

    Returns:
        dict: A dictionary of metrics for each party (growth, gains, decreases).
    """
    metrics = {
        "Republican": {"growth": 0, "gains": 0, "decreases": 0},
        "Democratic": {"growth": 0, "gains": 0, "decreases": 0},
    }

    previous_party, previous_jobs = None, None

    dtot = 0
    rtot = 0
    mtot = 0
    for entry in job_data:
        current_party = entry["party"]
        current_jobs = entry["jobs"]

        # Skip invalid or empty parties
        if current_party not in metrics:
            previous_party, previous_jobs = current_party, current_jobs
            print(f"Skipping entry with invalid party: {entry}")
            continue
        # Ensure previous party is a valid key
        if previous_party in metrics and previous_jobs is not None:
            # Calculate current month's growth, gains, or decreases
            growth = current_jobs - previous_jobs
            if previous_party == "Democratic":
                dtot += 1
            elif previous_party == "Republican":
                rtot += 1
            else:
                mtot += 1
            metrics[previous_party]["growth"] += growth
            if growth > 0:
                metrics[previous_party]["gains"] += growth
            else:
                metrics[previous_party]["decreases"] += abs(growth)

        previous_party, previous_jobs = current_party, current_jobs

    print(metrics["Democratic"])
    print(
        f"calculate_contributions: Democrat: {dtot}, Republican: {rtot}, Missing Party: {mtot}"
    )
    return metrics


def plot_trends(
    job_data: List[Dict[str, int]], graph_name: str, metrics: Dict[str, Dict[str, int]]
) -> None:
    graph_name += "_party_job_trends.png"
    party_colors = {"Democratic": "blue", "Republican": "red"}

    # Group data by president
    grouped_data = {}
    for entry in job_data:
        president = entry["president"]
        if president not in grouped_data:
            grouped_data[president] = {"party": entry["party"], "dates": [], "jobs": []}
        grouped_data[president]["dates"].append(entry["date"])
        grouped_data[president]["jobs"].append(entry["jobs"])

    # Create a single figure for all presidents
    plt.figure(figsize=(12, 6))

    # Plot each president's data with the respective party color
    for president, data in grouped_data.items():
        party = data["party"]
        plt.plot(
            data["dates"],
            data["jobs"],
            label=f"{president} ({party})",
            color=party_colors.get(party, "gray"),
        )

    legend_text = []
    for party, color in party_colors.items():
        growth = metrics[party]["growth"]
        gains = metrics[party]["gains"]
        decreases = metrics[party]["decreases"]
        legend_text.append(
            f"{party}\n"
            f"  Net Growth: {growth:>10}\n"
            f"  Jobs Created: {gains:>8}\n"
            f"  Jobs Lost: {decreases:>13}"
        )

    plt.legend(
        title="President (Party) and Contributions\n" + "\n".join(legend_text),
        loc="upper left",
        bbox_to_anchor=(1, 1),
        frameon=True,
    )

    plt.title(graph_name)
    plt.xlabel("Date")
    plt.ylabel("Employment (Thousands)")
    plt.grid(True, linestyle="--", alpha=0.7)
    plt.tight_layout()
    plt.savefig(graph_name, dpi=300, bbox_inches="tight")
    plt.close()


def plot_job_data_differences(
    job_data_1: List[Dict[str, int]], job_data_2: List[Dict[str, int]]
) -> None:
    # Ensure both datasets are sorted by date
    job_data_1.sort(key=lambda x: x["date"])
    job_data_2.sort(key=lambda x: x["date"])

    # Compute differences
    dates = [entry["date"] for entry in job_data_1]
    differences = [
        entry_1["jobs"] - entry_2["jobs"]
        for entry_1, entry_2 in zip(job_data_1, job_data_2)
    ]

    # Plot differences
    plt.figure(figsize=(12, 6))
    plt.plot(dates, differences, label="Job Data Differences", color="purple")
    plt.axhline(0, color="black", linestyle="--", linewidth=1)
    plt.title("Differences Between Job Data 1 and Job Data 2")
    plt.xlabel("Date")
    plt.ylabel("Employment Difference (Thousands)")
    plt.grid(True, linestyle="--", alpha=0.7)
    plt.legend()
    plt.tight_layout()
    plt.savefig("job_data_differences.png", dpi=300, bbox_inches="tight")
    plt.close()


def update_markdown(provided_metrics, corrected_metrics, template_file, output_file):
    # Read template content
    with open(template_file, "r") as template:
        content = template.read()

    # Create a mapping of placeholders to replacement values
    replacements = {
        "{{PROVIDED_REPUBLICAN}}": str(provided_metrics["Republican"]),
        "{{PROVIDED_DEMOCRATIC}}": str(provided_metrics["Democratic"]),
        "{{CORRECTED_REPUBLICAN}}": str(corrected_metrics["Republican"]),
        "{{CORRECTED_DEMOCRATIC}}": str(corrected_metrics["Democratic"]),
    }

    # Replace placeholders in the content
    for placeholder, value in replacements.items():
        if placeholder in content:
            content = content.replace(placeholder, value)
        else:
            print(f"Warning: Placeholder {placeholder} not found in template.")

    # Write the updated content back
    with open(output_file, "w") as output:
        output.write(content)


def main():
    cutoff = date(2012, 9, 30)
    provided_csv = "BLS_private_p7.csv"
    corrected_csv = "BLS_private_p7_corrected.csv"
    presidents_csv = "Presidents.csv"
    template_md = "conclusion_template.md"
    output_md = "conclusion.md"

    # Parse data
    provided_jobs = parse_data(provided_csv, cutoff)
    corrected_jobs = parse_data(corrected_csv, cutoff)
    # print(provided_jobs[:10])
    # print(corrected_jobs[:10])
    presidents = parse_presidents(presidents_csv)

    # Merge data with presidents
    merge_data(provided_jobs, presidents)
    merge_data(corrected_jobs, presidents)
    # for job in provided_jobs:
    #     if job["party"] == "Democratic":
    #         print(job)
    # for job in provided_jobs:
    #     if (
    #         job["date"].year >= 2000
    #         and job["date"].year <= 2005
    #         and job["party"] == "Democratic"
    #     ):
    #         print(job)

    # Calculate contributions
    provided_metrics = calculate_contributions(provided_jobs)
    corrected_metrics = calculate_contributions(corrected_jobs)

    # Plot job trends for both datasets
    plot_trends(provided_jobs, "provided", provided_metrics)
    plot_trends(corrected_jobs, "corrected", corrected_metrics)

    # Plot differences between datasets
    plot_job_data_differences(provided_jobs, corrected_jobs)

    # Update markdown file with contributions
    update_markdown(provided_metrics, corrected_metrics, template_md, output_md)


if __name__ == "__main__":
    main()
