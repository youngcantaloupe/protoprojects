import csv
from datetime import datetime
import matplotlib.pyplot as plt


def parse_job_data(file_path):
    """
    Parses job data from a CSV file.

    Args:
        file_path (str): Path to the job data CSV file.

    Returns:
        list: A list of dictionaries, each containing 'date' and 'jobs'.
    """
    job_data = []
    with open(file_path, "r") as file:
        reader = csv.reader(file)
        for index, row in enumerate(reader):
            if index > 5:  # Skip metadata rows
                year = int(row[0])
                for month_idx, value in enumerate(row[1:], start=1):
                    if value.strip():  # Skip empty values
                        month = datetime(year, month_idx, 1)
                        job_data.append({"date": month, "jobs": int(value)})
    return job_data


def parse_presidents(file_path):
    """
    Parses president term data from a CSV file.

    Args:
        file_path (str): Path to the president data CSV file.

    Returns:
        list: A list of dictionaries, each containing 'term_start', 'term_end', 'name', and 'party'.
    """
    presidents = []
    with open(file_path, "r") as file:
        reader = csv.DictReader(file)
        for row in reader:
            row["term_start"] = datetime.strptime(row["term start"], "%Y/%m/%d")
            row["term_end"] = datetime.strptime(row["term end"], "%Y/%m/%d")
            presidents.append(row)
    return presidents


def merge_president_data(job_data, presidents):
    """
    Merges president data into job data by adding 'president' and 'party' keys to each job entry.

    Args:
        job_data (list): List of job data dictionaries containing 'date' and 'jobs'.
        presidents (list): List of president term dictionaries.
    """
    for entry in job_data:
        date = entry["date"]
        for president in presidents:
            if president["term_start"] <= date <= president["term_end"]:
                entry["president"] = president["name"]
                entry["party"] = president["party"]
                break
        else:
            entry["president"] = ""
            entry["party"] = ""


def calculate_contributions(job_data):
    """
    Calculates the total contributions to employment growth for each party.

    Args:
        job_data (list): List of job data dictionaries containing 'date', 'jobs', 'president', and 'party'.

    Returns:
        dict: A dictionary with parties as keys and their total contributions as values.
    """
    contributions = {"Republican": 0, "Democratic": 0}
    previous_party = None
    previous_jobs = None

    for entry in job_data:
        current_party = entry["party"]
        current_jobs = entry["jobs"]

        if previous_party is not None:
            contributions[previous_party] += current_jobs - previous_jobs

        previous_party = current_party
        previous_jobs = current_jobs

    return contributions


def calculate_time_in_office(presidents):
    """
    Calculates the total time in office for each party.

    Args:
        presidents (list): List of president term dictionaries.

    Returns:
        dict: A dictionary with parties as keys and their time in office as (years, days).
    """
    party_durations = {"Republican": 0, "Democratic": 0}

    for president in presidents:
        term_start = president["term_start"]
        term_end = president["term_end"]
        party = president["party"]

        # Calculate term duration in days
        term_duration = (term_end - term_start).days

        # Accumulate days for the party
        if party in party_durations:
            party_durations[party] += term_duration

    # Convert total days to years and days
    party_time = {}
    for party, total_days in party_durations.items():
        years = total_days // 365
        days = total_days % 365
        party_time[party] = (years, days)

    return party_time


def plot_job_trends(job_data, file_prefix):
    """
    Plots employment trends over time by president and party.

    Args:
        job_data (list): List of job data dictionaries containing 'date', 'jobs', 'president', and 'party'.
        file_prefix (str): Prefix for the output plot file name.
    """
    file_name = f"{file_prefix}party_job_trends.png"
    party_colors = {"Democratic": "blue", "Republican": "red"}

    grouped_data = {}
    for entry in job_data:
        president = entry["president"]
        if president not in grouped_data:
            grouped_data[president] = {"party": entry["party"], "dates": [], "jobs": []}
        grouped_data[president]["dates"].append(entry["date"])
        grouped_data[president]["jobs"].append(entry["jobs"])

    plt.figure(figsize=(12, 6))
    for president, data in grouped_data.items():
        party = data["party"]
        plt.plot(
            data["dates"],
            data["jobs"],
            label=f"{president} ({party})",
            color=party_colors.get(party, "gray"),
        )

    plt.title(file_name)
    plt.xlabel("Date")
    plt.ylabel("Employment (Thousands)")
    plt.legend(title="President (Party)", loc="upper left", bbox_to_anchor=(1, 1))
    plt.grid(True, linestyle="--", alpha=0.7)
    plt.tight_layout()
    plt.savefig(file_name, dpi=300, bbox_inches="tight")
    plt.close()


def plot_data_differences(job_data_1, job_data_2):
    """
    Plots the differences between two job data datasets over time.

    Args:
        job_data_1 (list): First dataset of job data.
        job_data_2 (list): Second dataset of job data.
    """
    job_data_1.sort(key=lambda x: x["date"])
    job_data_2.sort(key=lambda x: x["date"])

    dates = [entry["date"] for entry in job_data_1]
    differences = [
        entry_1["jobs"] - entry_2["jobs"]
        for entry_1, entry_2 in zip(job_data_1, job_data_2)
    ]

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


def main():
    """
    Main function to parse data, merge president information, calculate contributions, and generate plots.
    """
    provided_csv = "BLS_private_p7.csv"
    corrected_csv = "BLS_private_p7_corrected.csv"
    presidents_csv = "Presidents.csv"

    provided_jobs = parse_job_data(provided_csv)
    corrected_jobs = parse_job_data(corrected_csv)
    presidents = parse_presidents(presidents_csv)

    merge_president_data(provided_jobs, presidents)
    merge_president_data(corrected_jobs, presidents)

    provided_contributions = calculate_contributions(provided_jobs)
    corrected_contributions = calculate_contributions(corrected_jobs)

    time_in_office = calculate_time_in_office(presidents)

    print("=== Contributions from Provided Dataset ===")
    print(f"Republican Contribution: {provided_contributions['Republican']}")
    print(f"Democratic Contribution: {provided_contributions['Democratic']}")

    print("\n=== Contributions from Corrected Dataset ===")
    print(f"Republican Contribution: {corrected_contributions['Republican']}")
    print(f"Democratic Contribution: {corrected_contributions['Democratic']}")

    print("\n=== Time in Office by Party ===")
    for party, (years, days) in time_in_office.items():
        print(f"{party}: {years} years and {days} days")

    plot_job_trends(provided_jobs, "provided_")
    plot_job_trends(corrected_jobs, "corrected_")
    plot_data_differences(provided_jobs, corrected_jobs)


if __name__ == "__main__":
    main()
