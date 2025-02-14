import csv
from datetime import datetime
import matplotlib.pyplot as plt


def parse_data(file_path, cutoff_date):
    """
    Parses job data from a CSV file and filters by cut_off date

    @param file_path: /path/to/file.csv
    @return job_data: A dictionary with key=year, value=list of monthly values
    """
    job_data = []
    with open(file_path, "r") as file:
        reader = csv.reader(file)
        for index, row in enumerate(reader):
            if index > 5:  # parse data after row 5
                year = int(row[0])
                for month_idx, value in enumerate(row[1:], start=1):
                    if value.strip():
                        month = datetime(year, month_idx, 1)
                        if month <= cutoff_date:
                            job_data.append({"date": month, "jobs": int(value)})
    return job_data


def parse_presidents(file_path):
    """ """
    presidents = []
    with open(file_path, "r") as file:
        reader = csv.DictReader(file)
        for row in reader:
            row["term start"] = datetime.strptime(row["term start"], "%Y/%m/%d")
            row["term end"] = datetime.strptime(row["term end"], "%Y/%m/%d")
            presidents.append(row)
    return presidents


def merge_data(job_data, presidents):
    for entry in job_data:
        date = entry["date"]
        has_president = False

        for president in presidents:
            if president["term start"] <= date <= president["term end"]:
                entry["president"] = president["name"]
                entry["party"] = president["party"]
                has_president = True
                break

        if not has_president:
            entry["president"] = ""
            entry["party"] = ""


def calculate_contributions(job_data):
    contributions = {"Republican": 0, "Democratic": 0}
    gains = {"Republican": 0, "Democratic": 0}
    decreases = {"Republican": 0, "Democratic": 0}

    previous_party = None
    previous_jobs = None

    for entry in job_data:
        current_party = entry["party"]
        current_jobs = entry["jobs"]

        if previous_jobs is not None and previous_party is not None:
            growth = current_jobs - previous_jobs
            contributions[previous_party] += growth

            if growth > 0:
                gains[previous_party] += growth
            else:
                decreases[previous_party] += abs(growth)

        previous_party = current_party
        previous_jobs = current_jobs

    print("Growth:", contributions.items())
    print("Gains:", gains.items())
    print("Decreases:", decreases.items())

    return contributions, gains, decreases


def plot_trends(job_data, graph_name, contributions, gains, decreases):
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
        growth = contributions.get(party, 0)
        gain = gains.get(party, 0)
        decrease = decreases.get(party, 0)
        legend_text.append(
            f"{party} Net Growth: {growth}\n    Jobs Created: {gain}\n    Jobs Lost: -{decrease}"
        )

    plt.legend(
        title="President (Party) and Contributions \n" + "\n".join(legend_text),
        loc="upper left",
        bbox_to_anchor=(1, 1),
    )

    plt.title(graph_name)
    plt.xlabel("Date")
    plt.ylabel("Employment (Thousands)")
    plt.grid(True, linestyle="--", alpha=0.7)
    plt.tight_layout()
    plt.savefig(graph_name, dpi=300, bbox_inches="tight")
    plt.close()


def plot_job_data_differences(job_data_1, job_data_2):
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


def main():
    provided_BLS_csv = "BLS_private_p7.csv"
    corrected_BLS_csv = "BLS_private_p7_corrected.csv"
    presidents_csv = "Presidents.csv"
    cutoff_date = datetime(2012, 8, 31)

    ext_provided = "provided"
    ext_corrected = "corrected"

    provided_job_data = parse_data(provided_BLS_csv, cutoff_date)
    corrected_job_data = parse_data(corrected_BLS_csv, cutoff_date)

    presidents = parse_presidents(presidents_csv)

    merge_data(provided_job_data, presidents)
    merge_data(corrected_job_data, presidents)

    provided_contributions, provided_gains, provided_decreases = (
        calculate_contributions(provided_job_data)
    )
    corrected_contributions, corrected_gains, corrected_decreases = (
        calculate_contributions(corrected_job_data)
    )

    plot_trends(
        provided_job_data,
        ext_provided,
        provided_contributions,
        provided_gains,
        provided_decreases,
    )
    plot_trends(
        corrected_job_data,
        ext_corrected,
        corrected_contributions,
        corrected_gains,
        corrected_decreases,
    )

    plot_job_data_differences(provided_job_data, corrected_job_data)


if __name__ == "__main__":
    main()
